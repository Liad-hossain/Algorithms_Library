struct Edge{
  int w=INT_MAX,to=-1;
};

struct prim{
  vector<vector<int>>adj;
  vector<Edge>min_e;
  vector<pair<int,int>>edge;
  vector<bool>selected;
  int N;
  prim(int n=0){
    for(int i=0;i<adj.size();i++)adj[i].clear();
    adj.resize(n+2);
    for(int i=0;i<=n;i++)adj[i].resize(n+2);
    min_e.resize(n+2);
    selected.resize(n+2);
    for(int i=0;i<=n;i++)selected[i]=false;
    N=n;
  }

  //0-based
  int apply(){
    min_e[0].w=0;
    int tot=0;
    for(int i=0;i<N;i++){
      int v=-1;
      for(int j=0;j<N;j++){
        if(!selected[j] && (v==-1 || min_e[j].w<min_e[v].w))
          v=j;
      }

      if(min_e[v].w==INT_MAX)return -1;
      tot+=min_e[v].w;
      selected[v]=true;
      if(min_e[v].to!=-1){
        edge.push_back({v,min_e[v].to});
      }
      for(int to=0;to<N;to++){
        if(min_e[to].w>adj[v][to]){
          min_e[to]={adj[v][to],v};
        }
      }
    }
    return tot;
  }
};
