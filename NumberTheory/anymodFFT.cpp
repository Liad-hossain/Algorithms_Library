struct CD{
double x,y;
CD(double a=0,double b=0):x(a),y(b){}
CD operator+(const CD& o){return {x+o.x,y+o.y};}
CD operator-(const CD& o){return {x-o.x,y-o.y};}
CD operator*(const CD& o){return
{x*o.x-y*o.y,x*o.y+o.x*y};}
void operator/=(double d){ x/=d;y/=d;}
double real(){return x;}
double imag(){return y;}
};
CD conj(const CD &c){return CD(c.x,-c.y);}
const double PI=acos(-1.0L);
const int mod=1e9+7;
namespace FFT{
int N;
vector<int>perm;
vector<CD>wp[2];
void precalculate(int n){
assert((n&(n-1))==0);
N=n;
perm=vector<int>(N,0);
for(int k=1;k<N;k<<=1){
for(int i=0;i<k;i++){
perm[i]<<=1;
perm[i+k]=1+perm[i];
}}
wp[0]=wp[1]=vector<CD>(N);
for(int i=0;i<N;i++){
wp[0][i]=CD(cos(2*PI*i/N),sin(2*PI*i/N));
wp[1][i]=CD(cos(2*PI*i/N),-sin(2*PI*i/N));
}}
void fft(vector<CD>&v,bool invert=false){
if(v.size()!=perm.size()) precalculate(v.size());
for(int i=0;i<N;i++){
if(i<perm[i]) swap(v[i],v[perm[i]]);
}
for(int len=2;len<=N;len*=2){
for(int i=0,d=N/len;i<N;i+=len){
for(int j=0,idx=0;j<len/2;j++,idx+=d){
CD x=v[i+j];
CD y=wp[invert][idx]*v[i+j+len/2];
v[i+j]=x+y;
v[i+j+len/2]=x-y;
}}}
if(invert){
for(int i=0;i<N;i++) v[i]/=N;
}}
void pairfft(vector<CD>&a,vector<CD>&b,bool
invert=false){
int n=a.size();
vector<CD>p(n);
for(int i=0;i<n;i++) p[i]=a[i]+b[i]*CD(0,1);
fft(p,invert);
p.push_back(p[0]);
for(int i=0;i<n;i++){
if(invert){
a[i]=CD(p[i].real(),0);
b[i]=CD(p[i].imag(),0);
}
else{
a[i]=(p[i]+conj(p[n-i]))*CD(0.5,0);
b[i]=(p[i]-conj(p[n-i]))*CD(0,-0.5);
}}}
vector<ll>multiply(const vector<ll>&a,const
vector<ll>&b){
int n=1;
while(n<(int)(a.size()+b.size()))n<<=1;
vector<CD>fa(a.begin(),a.end()),fb(b.begin(),b.end());
fa.resize(n);fb.resize(n);
pairfft(fa,fb);
for(int i=0;i<n;i++) fa[i]=fa[i]*fb[i];
fft(fa,true);
vector<ll>ans(n);
for(int i=0;i<n;i++){
ans[i]=round(fa[i].real());
}
return ans;}
const ll B=sqrt(mod)+1;
vector<ll> anyMod(const vector<ll>&a,const
vector<ll>&b){
int n=1;
while(n<(int)(a.size()+b.size())) n<<=1;
vector<CD>al(n),ar(n),bl(n),br(n);
for(int i=0;i<(int)a.size();i++){
al[i]=a[i]%mod/B,ar[i]=a[i]%mod%B;
}
for(int i=0;i<(int)b.size();i++){
bl[i]=b[i]%mod/B,br[i]=b[i]%mod%B;
}
pairfft(al,ar);pairfft(bl,br);
for(int i=0;i<n;i++){
CD LL=(al[i]*bl[i]),LR=(al[i]*br[i]);
CD RL=(ar[i]*bl[i]),RR=(ar[i]*br[i]);
al[i]=LL;ar[i]=LR;
bl[i]=RL;br[i]=RR;
}
pairfft(al,ar,1);pairfft(bl,br,1);
vector<ll>ans(n);
for(int i=0;i<n;i++){
ll right=round(br[i].real()),left=round(al[i].real());
ll mid=round(round(bl[i].real())+round(ar[i].real()));
ans[i]=((left%mod)*B*B+(mid%mod)*B+right)%mod;
}
return ans;}}