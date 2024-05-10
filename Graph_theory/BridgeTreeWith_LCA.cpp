const int mx=1e5+3;
vector<int>graph[mx];
int in[mx],low[mx],color[mx],col,timer;
int Lca[mx][25],Log[mx],level[mx];
bool vis[mx];
stack<int>s;
void dfs(int node,int par)
{
  in[node]=low[node]=++timer;
  vis[node]=true;
  s.push(node);
  for(int child:graph[node]){
    if(child==par)continue;
    if(!vis[child]){
      dfs(child,node);
      low[node]=min(low[node],low[child]);
    }
    else low[node]=min(low[node],in[child]);
  }

  if(in[node]==low[node]){
    col++;
    while(!s.empty()){
      int val=s.top();
      color[val]=col;
      s.pop();
      if(val==node)break;
    }
  }
}
void dfs2(int node,int par,int lvl){
  vis[node]=true;
  Lca[color[node]][0]=(par==-1?-1:color[par]);
  level[color[node]]=lvl;
  for(int child:graph[node]){
    if(vis[child])continue;
    if(color[node]==color[child])dfs2(child,par,lvl);
    else dfs2(child,node,lvl+1);
  }
}
void calcLca(int n){
  Log[1]=0;
  for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
  for(int i=1;i<=n;i++){
    for(int j=0;j<25;j++)Lca[i][j]=-1;
  }
  dfs2(1,-1,0);
  for(int j=1;j<25;j++){
    for(int i=1;i<=n;i++){
      int par=Lca[i][j-1];
      if(par!=-1)Lca[i][j]=Lca[par][j-1];
    }
  }
}
int getLca(int a,int b)
{
  if(level[a]>level[b])swap(a,b);
  int d=level[b]-level[a];
  while(d>0){
    int i=Log[d];
    b=Lca[b][i];
    d-=(1<<i);
  }

  if(a==b)return a;
  for(int i=22;i>=0;i--){
    if(Lca[a][i]!=-1 && Lca[a][i]!=Lca[b][i]){
      a=Lca[a][i],b=Lca[b][i];
    }
  }
  return Lca[a][0];
}
int getDist(int a,int b){
  a=color[a],b=color[b];
  int lca=getLca(a,b);
  return level[a]+level[b]-2*level[lca];
}
int getanc(int u, int d) {
    for (int k=0; k<25; k++)
        if (d & (1<<k))
            u = Lca[u][k];
    return u;
}
void makeBridgeTree(int n){
  dfs(1,-1);
  memset(vis,false,sizeof(vis));
  calcLca(n);
}

