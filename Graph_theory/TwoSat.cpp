struct TwoSat{
    vector<vector<int>>graph,rev;
    vector<int>vis,comp,order,res;
    void init(int n=0){
        graph.resize(2*n+2);
        rev.resize(2*n+2);
        for(int i=0;i<=2*n;i++){
            graph[i].clear(),rev[i].clear();
        }
    }
    inline int value(int a){
        if(a<0){
            a=-a;a--;
            return ((a)<<1)+1;
        }
        a--;
        return ((a)<<1);
    }
    inline void AddEdge(int u,int v){
        u=value(u),v=value(v);
        graph[u].push_back(v);
        rev[v].push_back(u);
    }
    inline void add_or(int a,int b){ 
        AddEdge(-a,b);
        AddEdge(-b,a);
    }
    inline void add_xor(int a,int b){
        add_or(a,b);
        add_or(-a,-b);
    }
    inline void add_and(int a,int b){
        add_or(a,b);
        add_or(a,-b);
        add_or(-a,b);
    }
    inline void add_xnor(int a,int b){
        add_or(a,-b);
        add_or(-a,b);
    }
    inline void force_true(int x){
        AddEdge(-x,x);
    }
    inline void force_false(int x){
        AddEdge(x,-x);
    }

    void topsort(int node){
        vis[node]=1;
        for(int child:graph[node]){
            if(!vis[child])topsort(child);
        }
        order.push_back(node);
    }
    void dfs(int node,int col){
        comp[node]=col;
        for(int child:rev[node]){
            if(comp[child]==-1)dfs(child,col);
        }
    }
    bool ok(int n){
        vis.resize(2*n+2);
        comp.resize(2*n+2);
        for(int i=0;i<2*n;i++)vis[i]=0,comp[i]=-1;
        order.clear();
        res.clear();
        for(int i=0;i<2*n;i++){
            if(!vis[i])topsort(i);
        }
        reverse(order.begin(),order.end());
        for(int i=0,j=0;i<order.size();i++){
            if(comp[order[i]]==-1)dfs(order[i],++j);
        }

        for(int i=0;i<2*n;i+=2){
            if(comp[i]==comp[i+1])return false;
            if(comp[i]>comp[i+1])res.push_back(i/2+1);
        }
        return true;
    }
};