const int N=2e5+5; /// double of given N
const int LOG=20;
int timer=0; /// timer
int flat[N]; /// flat tree after euler tour
vector<int> g[N]; /// input graph
///vector<int> w[N],if there is a weight in edge
int par[N],dep[N]; /// normal parent and depth
int st[N],en[N]; /// start and end time
/// for lca in sparse table
int table[LOG][N],a[N],id[N],lg[N],cur=0;
int val[N]; /// value in node
void dfs(int node,int p){
  st[node]= ++timer;
  flat[timer]=node;
  par[node]=p;
  dep[node]=dep[p]+1;
  for(int i=0;i<(int)g[node].size();i++){
    if(g[node][i]==p){
      continue; }
    dfs(g[node][i],node);
    /// if there is weight we just pass the weight
  }
  en[node]= ++timer;
  flat[timer]=node;
  a[++cur]=node;
  id[node]=cur;
}
void LOG_build(int n){
  lg[0]=lg[1]=0;
  for(int i=2;i<=n;i++){
    lg[i]=lg[i>>1]+1;
  }
}
void build(int n,int root){
  /// n == total number of nodes
  /// make sure cur and timer == 0
  dfs(root,root);
  for(int i=1;i<=n;i++){
  table[0][i]=a[i];
  }
  for(int l=0;l<LOG-1;l++){
    for(int i=1;i<=n;i++){
      table[l+1][i]=table[l][i];
      if(i+(1<<l)<=n &&
      dep[table[l][i+(1<<l)]]<dep[table[l][i]]){
        table[l+1][i]=table[l][i+(1<<l)];
      }
    }
  }
}
int lca(int u,int v){
  if(en[u]>en[v])swap(u,v);
  if(st[v]<=st[u] and en[u]<=en[v])
    return v;
  int l=lg[id[v]-id[u]+1];
  int p1=id[u],p2=id[v]-(1<<l)+1;
  if(dep[table[l][p1]] < dep[table[l][p2]]){
  return par[table[l][p1]];
  }
  else{
    return par[table[l][p2]];
  }
}
struct query
{
int SQRT = 400;
int l, r, id;
bool operator< (query b){
query a = *this;
return make_pair(a.l/SQRT,a.r) <
make_pair(b.l/SQRT,b.r);
}
/// ei sorting ta compare function pathay diyeo
///kora jay
};
/// extra memory for problem
query qs[N];
int ans[N],curans=0;
int cnt[N];
bool vis[N];
void add(int x){
if(cnt[x]==0){
curans++;
}
cnt[x]++;
}
void sub(int x){
if(cnt[x]==1){
curans--;
}
cnt[x]--;
}
void check(int idx){
if(!vis[idx]){
vis[idx]=1;
add(val[idx]);
}
else{
vis[idx]=0;
sub(val[idx]);
} }
void mo_algo(int q){
sort(qs+1,qs+q+1);
int curL=qs[1].l, curR=curL-1;
for(int i=1;i<=q;i++){
	int L=qs[i].l,R=qs[i].r;
while(curL < L) check(flat[curL++]);
while(curL > L) check(flat[--curL]);
while(curR < R) check(flat[++curR]);
while(curR > R) check(flat[curR--]);
int LCA=lca(flat[curL],flat[curR]);
/// for node weight
if(flat[curL]!=LCA or flat[curR]!=LCA){
check(LCA);
}
ans[qs[i].id] = curans;
if(flat[curL]!=LCA or flat[curR]!=LCA){
check(LCA);
}
/// for edge weight
if(flat[curL]==LCA or flat[curR]==LCA){
check(LCA);
}
ans[qs[i].id] = curans;
if(flat[curL]==LCA or flat[curR]==LCA){
check(LCA);
} } }
void compress(int n){
/// see in mo-algo
}
void solve(){
int n,q;
cin>>n>>q;
for(int i=1;i<=n;i++){
cin>>val[i];
}
compress(n);
for(int i=1;i<n;i++){
int x,y;
cin>>x>>y;
g[x].push_back(y);
g[y].push_back(x);
}
LOG_build(n);
build(n,1);
/// for edge weight
for(int i=1;i<=n;i++){
for(int adj=0;adj<(int)g[i].size();adj++){
	if(dep[i]>dep[g[i][adj]]){
val[i]=w[i][adj];
}
else{
val[g[i][adj]]=w[i][adj];
} } }
for(int i=1;i<=q;i++){
int u,v;
cin>>u>>v;
if(st[u]>st[v]){
swap(u,v);
}
int LCA=lca(u,v);
if(LCA==u) {
qs[i].l=st[u],qs[i].r=st[v];
}
else{
qs[i].l=en[u],qs[i].r=st[v];
}
qs[i].id=i;
}
mo_algo(q);
for(int i=1;i<=q;i++){
cout<<ans[i]<<nl;
}
}
