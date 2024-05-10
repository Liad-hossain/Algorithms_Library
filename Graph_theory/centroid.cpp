struct CD{
  vector<vector<int>>graph;
  vector<int>d[20],par,level,sub,ans,vis;
  CD(int n){
    graph.resize(n+3),par.resize(n+3);
    level.resize(n+3),sub.resize(n+3);
    ans.resize(n+3),vis.resize(n+3);
    for(int i=0;i<20;i++)d[i].resize(n+3);
    for(int i=1;i<=n;i++)ans[i]=1e8;
  }
  void calc(int node,int p){
    sub[node]=1;
    for(int child:graph[node]){
      if(child==p || vis[child])continue;
      calc(child,node);sub[node]+=sub[child];}
  }
  int centroid(int node,int p,int sz){
    for(int child:graph[node]){
      if(child==p || vis[child])continue;
      if(sub[child]>sz)return centroid(child,node,sz);}
    return node;
  }
  void dfs(int node,int p,int lvl){
    d[lvl][node]=0;
    if(p!=-1)d[lvl][node]=d[lvl][p]+1;
    for(int child:graph[node]){
      if(child==p || vis[child])continue;
      dfs(child,node,lvl);}
  }
  //call this function
  void decompose(int node,int p){
    calc(node,-1);
    int c=centroid(node,-1,sub[node]>>1);
    vis[c]=1,par[c]=p,level[c]=0;
    if(p!=-1)level[c]=level[p]+1;
    dfs(c,-1,level[c]);
    for(int child:graph[c]){
      if(child==p || vis[child])continue;
      decompose(child,c);}
  }
  void update(int node){
    for(int v=node;v!=-1;v=par[v]){
      ans[v]=min(ans[v],d[level[v]][node]);}
  }
  int query(int node){
    int ret=1e8;
    for(int v=node;v!=-1;v=par[v]){
      ret=min(ret,d[level[v]][node]+ans[v]);}
    return ret;
  }
};
