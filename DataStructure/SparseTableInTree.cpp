// Sparse Table in a tree
const int N=1e5+5;
const int LOG=21;
int par[N][LOG],tablemin[N][LOG],tablemax[N][LOG];
int dep[N];
vector <pair<int,int>> g[N];
void dfs (int n,int p,int depth)
{
dep[n]=depth;
par[n][0]=p;
for(auto adj:g[n])
{
if(adj.ff==p) continue;
tablemin[adj.ff][0]=tablemax[adj.ff][0]=adj.ss;
dfs(adj.ff,n,depth+1);
}}
void precal(int root , int n)
{
dfs(root,-1,1);
for(int k=1;k<LOG;k++) {
for(int i=1;i<=n;i++) {
if(par[i][k-1]!=-1){
par[i][k]=par[par[i][k-1]][k-1];
tablemin[i][k]=min(tablemin[i][k-1],
tablemin[par[i][k-1]][k-1]);
tablemax[i][k]=max(tablemax[i][k-1],
tablemax[par[i][k-1]][k-1]);}
else
par[i][k]=-1;}
}}
pair<int,pair<int,int>> lca(int u,int v)
{
if(u==v) return {u,{0,0}};
if(dep[u]<dep[v])
{ /// u node take nichey dhorbo
swap(u,v);
}
pair<int,pair<int,int>> ans={u,{INT_MIN,INT_MAX}};
/// first e same level e ansi duitake
int diff=dep[u]-dep[v];
for(int i=LOG-1;i>=0;i--)
{
if(diff>=(1<<i))
{
diff-=(1<<i);
ans.ss.ff=max(ans.ss.ff,tablemax[u][i]);
ans.ss.ss=min(ans.ss.ss,tablemin[u][i]);
u=par[u][i];
}}
if(u==v) return ans;
/// ekhane lca er just porer node dui tate ansi
for(int i=LOG-1;i>=0;i--)
{
if(par[u][i]!=par[v][i])
{
ans.ss.ff = max(ans.ss.ff, tablemax[u][i]);
ans.ss.ff = max(ans.ss.ff, tablemax[v][i]);
ans.ss.ss = min(ans.ss.ss, tablemin[u][i]);
ans.ss.ss = min(ans.ss.ss, tablemin[v][i]);
u=par[u][i];
v=par[v][i];
}}
ans.ss.ff = max(ans.ss.ff, tablemax[u][0]);
ans.ss.ff = max(ans.ss.ff, tablemax[v][0]);
ans.ss.ss = min(ans.ss.ss, tablemin[u][0]);
ans.ss.ss = min(ans.ss.ss, tablemin[v][0]);
ans.ff=par[v][0];
return ans;
}