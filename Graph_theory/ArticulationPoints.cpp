const int mx=5e5+2;
vector<int>g[mx];
bool isCutPoint[mx],vis[mx];
int in[mx],low[mx],timer;
void dfs(int node,int par){
  vis[node]=true;
  in[node]=low[node]=++timer;
  int ch=0;
  for(int child:g[node]){
    if(child==par)continue;
    if(!vis[child]){
      dfs(child,node);
      low[node]=min(low[node],low[child]);
      ch++;
      if(low[child]>=in[node] && par!=-1)isCutPoint[node]=1;
    }
    else low[node]=min(low[node],in[child]);
  }
  if(par==-1 && ch>1)isCutPoint[node]=1;
}
