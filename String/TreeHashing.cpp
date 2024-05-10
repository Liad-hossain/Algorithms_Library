const int N=2e5+5;
vector<int>g[N];
int sub[N];
#define int long long
#define ff first
#define ss second
typedef pair<int,int> pp;
const pp mod={1111211111,1111115111};
const int base=359;
ostream& operator<<(ostream& os,pp Hash){
    return os<<"("<<Hash.ff<<", "<<Hash.ss<<")";
}
pp operator+(pp a,int x){return {a.ff+x,a.ss+x};}
pp operator-(pp a,int x){return {a.ff-x,a.ss-x};}
pp operator*(pp a,int x){return {a.ff*x,a.ss*x};}
pp operator%(pp a,int x){return {a.ff%x,a.ss%x};}
pp operator+(pp a,pp x){return {a.ff+x.ff,a.ss+x.ss};}
pp operator-(pp a,pp x){return {a.ff-x.ff,a.ss-x.ss};}
pp operator*(pp a,pp x){return {a.ff*x.ff,a.ss*x.ss};}
pp operator%(pp a,pp m){return {a.ff%m.ff,a.ss%m.ss};}
pp power[N];
void precalc(){
    power[0]={1,1};
    for(int i=1;i<N;i++){
        power[i]=(power[i-1]*base)%mod;
    }
}
pp hashlist[N];
//Calculates hashes of all prefixes of s including empty prefix
//that means here string must be 1 indexing
void TreeHashing(int node,int par){
  vector<pp>h1,h2;
  sub[node]=1;
  for(int child:g[node]){
    if(child==par)continue;
    TreeHashing(child,node);
    sub[node]+=sub[child];
    h1.push_back({hashlist[child].first,sub[child]});
    h2.push_back({hashlist[child].second,sub[child]});
  }
  sort(h1.begin(),h1.end());
  sort(h2.begin(),h2.end());
  hashlist[node]={31,53};
  int cnt=1;
  for(int i=0;i<(int)h1.size();i++){
    pp hashval={h1[i].first,h2[i].first};
    hashlist[node]=(hashlist[node]+
        (power[cnt]*hashval)%mod)%mod;
    cnt+=h1[i].second;
  }
  pp hashval={37,97};
  hashlist[node]=(hashlist[node]+
      (power[cnt]*hashval)%mod)%mod;
}
