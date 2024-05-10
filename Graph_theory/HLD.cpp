struct HLD{
    vector<int>heavy,head,par,start,flat,sub,level,Log;
    vector<vector<int>>graph,Lca;
    int timer,N;
    void init(int n){
        N=n,timer=0;
        heavy.resize(n+4),head.resize(n+4);
        par.resize(n+4),start.resize(n+4);
        sub.resize(n+4),Log.resize(n+4);
        level.resize(n+4),graph.resize(n+4);
        Lca.resize(n+4),flat.resize(n+4);
        for(int i=1;i<=N;i++){
            for(int j=0;j<24;j++)Lca[i].push_back(-1);
        }
        Log[1]=0;
        for(int i=2;i<=N;i++)Log[i]=Log[i/2]+1;
    }
    void dfs(int node,int p,int lvl){
        par[node]=p;
        Lca[node][0]=p;
        level[node]=lvl;
        sub[node]=1;
        int tmp=0;
        heavy[node]=-1;
        for(int child:graph[node]){
            if(child==p)continue;
            dfs(child,node,lvl+1);
            sub[node]+=sub[child];
            if(sub[child]>tmp)
                tmp=sub[child],heavy[node]=child;
        }
    }
    void decompose(int node,int p,int h){
        head[node]=h;
        start[node]=++timer;
        flat[timer]=node;
        if(heavy[node]!=-1)decompose(heavy[node],node,h);
        for(int child:graph[node]){
            if(child==p || child==heavy[node])continue;
            decompose(child,node,child);
        }
    }
    void calcLca(){
        for(int j=1;j<24;j++){
            for(int i=1;i<=N;i++){
                int p=Lca[i][j-1];
                if(p!=-1)Lca[i][j]=Lca[p][j-1];
            }
        }
    }
    void computeHLD(){
        dfs(1,-1,0);
        decompose(1,-1,1);
        calcLca();
    }
    int getLca(int a,int b){
        if(level[a]>level[b])swap(a,b);
        int d=level[b]-level[a];
        while(d>0){
            int i=Log[d];
            b=Lca[b][i];
            d-=(1<<i);
        }
        if(a==b)return a;
        for(int i=23;i>=0;i--){
            if(Lca[a][i]!=-1 && Lca[a][i]!=Lca[b][i]){
                a=Lca[a][i],b=Lca[b][i];
            }
        }
        return Lca[a][0];
    }
    inline void update(int a,int b,int val){
        int lca=getLca(a,b);
        while(head[a]!=head[lca]){
            Update(start[head[a]],start[a],val);
            a=par[head[a]];
        }
        Update(start[lca],start[a],val);
        while(head[b]!=head[lca]){
            Update(start[head[b]],start[b],val);
            b=par[head[b]];
        }
        Update(start[lca],start[b],val);
        Update(start[lca],start[lca],-val);
    }
    inline int query(int a,int b){
        int lca=getLca(a,b);
        int res=0;
        while(head[a]!=head[lca]){
            res+=Query(start[head[a]],start[a]);
            a=par[head[a]];
        }
        res+=Query(start[lca],start[a]);
        while(head[b]!=head[lca]){
            res+=Query(start[head[b]],start[b]);
            b=par[head[b]];
        }
        res+=Query(start[lca],start[b]);
        res-=Query(start[lca],start[lca]);
        return res;
    }
};