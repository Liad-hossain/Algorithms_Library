struct kosaraju{
    vector<vector<pair<int,int>>>g,rev;
    vector<bool>vis;
    vector<int>order,component,cycle;
    int col;
    void init(int n){
        vis.resize(n+5,0);
        g.resize(n+5);
        rev.resize(n+5);
        col=0;order.clear();
        cycle.resize(n+5);
    }
    void AddEdge(int u,int v,int w=0){
        g[u].push_back({v,w});
        rev[v].push_back({u,w});
    }
    void dfs1(int node){
        vis[node]=1;
        for(auto child:g[node]){
            if(!vis[child.first])dfs1(child.first);
        }
        order.push_back(node);
    }

    void dfs2(int node){
        vis[node]=1;
        cycle[node]=col;
        component.push_back(node);
        for(auto child:rev[node]){
            if(!vis[child.first]){
                dfs2(child.first);
            }
        }
    }
    void Apply(int n){
        for(int i=1;i<=n;i++){
            if(!vis[i])dfs1(i);
        }
        for(int i=0;i<=n;i++)vis[i]=0;
        reverse(order.begin(),order.end());
        for(int v:order){
            if(!vis[v]){
                component.clear();
                col++;
                dfs2(v);
            }
        }
    }
};