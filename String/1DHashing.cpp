#define int long long
typedef pair<int,int> pp;
const pp mod={1111211111, 1111115111};
const int base=359;
const int N=1e6+5;
ostream& operator<<(ostream& os, pp Hash) {
return os<<"("<<Hash.ff<<", "<<Hash.ss<<")";
}
pp operator+ (pp a, int x)
{return {a.ff + x, a.ss + x};}
pp operator- (pp a, int x)
{return {a.ff - x, a.ss - x};}
pp operator* (pp a, int x)
{return {a.ff * x, a.ss * x};}
pp operator% (pp a, int x)
{return {a.ff % x, a.ss % x};}
pp operator+ (pp a, pp x)
{return {a.ff + x.ff, a.ss + x.ss};}
pp operator- (pp a, pp x)
{return {a.ff - x.ff, a.ss - x.ss};}
pp operator* (pp a, pp x)
{return {a.ff * x.ff, a.ss * x.ss};}
pp operator% (pp a, pp m)
{return {a.ff % m.ff, a.ss % m.ss};}
// Calculate all powers of the base
// This should be called before everything
pp power[N];
// inverse of base for each mod
pp inv;
pp invbase[N];
pp bigmod(pp a, int p) {
  if (p==0) return {1,1};
  pp ans=bigmod(a,p/2);
  ans=(ans*ans)%mod;
  if(p%2) ans=(ans*a)%mod;
  return ans;
}
pp inverse(pp a) {
return bigmod(a,(mod.ff-1)*(mod.ss-1)-1);
}
void precal(){
  power[0]={1,1};
  for(int i=1;i<N;i++)
  power[i]=(power[i-1]*base)%mod;
  inv=inverse(power[1]);
}
pp Hash(string &s){
  pp ans={0,0};
  for(int i=0;i<(int)s.size();i++)
    ans=(ans*base+s[i])%mod;
  return ans;
}
pp append(pp currenthash,char ch){
return (currenthash*base+ch)%mod;
}
///length=currenthash length before prepend
pp prepend(pp currenthash,int length,char ch){
    return (power[length]*ch+currenthash)%mod;
}
///replace a with b, i= current len-1
pp replace(pp currenthash,int i,char a,char b){
return ((currenthash+power[i]*(b-a))%mod+mod)%mod;
}
pp pop_back(pp Hash, char c) {
return (((Hash-c)*inv)%mod+mod)%mod;
}
///len=current hash len before pop_front
pp pop_front(pp Hash, int len, char c) {
return ((Hash-power[len-1]*c)%mod+mod)%mod;
}
pp concat(pp lefthash,pp righthash,int k) {
return (lefthash*power[k]+righthash)%mod;
}
///Calculates Hash of string with size length
///repeated cnt times
///This is O(log n). For O(1), pre-calculate inverses
pp repeat(pp Hash, int length, int cnt) {
  pp mul=(power[length*cnt]-1)*
  inverse(power[length]-1);
  mul=(mul%mod+mod)%mod;
  pp ans=(Hash*mul)%mod;
  if(power[length].ff==1)ans.ff=Hash.ff*cnt;
  if(power[length].ss==1)ans.ss=Hash.ss*cnt;
  return ans;
}
pp hashlist[N];
// Calculates hashes of all prefixes of s including
///empty prefix
// that means here string must be 1 indexing
void prefixhashing(string &s){
  int n=(int)s.size()-1;
  hashlist[0]={0,0};
  for(int i=1;i<=n;i++)
  hashlist[i]=(hashlist[i-1]*base+s[i])%mod;
}
// Calculates Hash of substring s[l..r] (1 indexed)
pp substringhash(int l,int r){
  int length=(r-l+1);
  return (hashlist[r]-hashlist[l-1]*
  power[length]%mod+mod)%mod;
}
pp substringinv(int l,int r){
  int length=(r-l+1);
  return inverse((hashlist[r]-hashlist[l-1]*
  power[length]%mod+mod)%mod);
}
