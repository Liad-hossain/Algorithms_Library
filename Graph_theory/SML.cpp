vector<int> g[N];
set<int> s[N];
int cr[N],num[N],score[N];
void dfs(int n,int p){
cr[n]=n;
for(int adj:g[n]){
	if(adj!=p) dfs(adj,n);
}
s[cr[n]].insert(num[n]);
for(int adj:g[n]){
if(adj!=p){
if(s[cr[n]].size()<s[cr[adj]].size())
swap(cr[n],cr[adj]);
for(int x:s[cr[adj]])
s[cr[n]].insert(x);
}}
score[n]=(int)s[cr[n]].size();
}