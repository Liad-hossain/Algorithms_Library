#define inf 9000000000000000000 //9e18
struct Edge{
int a,b;
long long int cost;
};
struct BellmanFord{
vector<Edge>e;
vector<long long int>dist;
vector<int>par;
BellmanFord(int n=0){	
dist.resize(n+2);
par.resize(n+2);
for(int i=1;i<=n;i++)dist[i]=inf;
}
bool apply(int n,int root){
dist[root]=0;
for(int i=1;i<n;i++){
for(int j=0;j<e.size();j++){
if(dist[e[j].a]<inf){
if (dist[e[j].b] > dist[e[j].a] + e[j].cost)
{
dist[e[j].b] = dist[e[j].a] + e[j].cost;
par[e[j].b] = e[j].a;
}
}
}
for(int j=0;j<e.size();j++){
if(dist[e[j].b]>dist[e[j].a]+e[j].cost)return false;
}
return true;
}
};
