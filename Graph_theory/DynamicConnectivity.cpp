#include<bits/stdc++.h>
using namespace std;
#define nl '\n'
#define ff first
#define ss second
#define int long long int
const int N=3e5+5;
char op[N<<1];
stack<int>st;
int ans;
int par[N],rnk[N],other[N<<1],u[N<<1],v[N<<1];
int findpar(int a){
  while(par[a]!=a)a=par[a];
  return a;
}

void unit(int a,int b){
  a=findpar(a),b=findpar(b);
  if(a==b)return;
  if(rnk[a]<rnk[b])swap(a,b);
  par[b]=a;
  rnk[a]+=rnk[b];
  st.push(b);
  ans--;
}

void rollback(int now){
  while(st.size()>now){
    ans++;
    int u=st.top();st.pop();
    rnk[par[u]]-=rnk[u];
    par[u]=u;
  }
}

void call(int l,int r){
  if(l==r){
    if(op[l]=='?'){
      cout<<ans<<nl;
    }
    return;
  }

  int m=(l+r)>>1;
  int now=st.size();
  for(int i=m+1;i<=r;i++){
    if(other[i]<l){
      unit(u[i],v[i]);
    }
  }

  call(l,m);
  rollback(now);
  for(int i=l;i<=m;i++){
    if(other[i]>r){
      unit(u[i],v[i]);
    }
  }

  call(m+1,r);
  rollback(now);
}

void solve(){
  int n,k;
  cin>>n>>k;
  if(!k)return;
  for(int i=1;i<=n;i++)par[i]=i,rnk[i]=1;
  map<pair<int,int>,int>mp;
  for(int i=1;i<=k;i++){
    cin>>op[i];
    if(op[i]=='?')continue;
    cin>>u[i]>>v[i];
    if(u[i]>v[i])swap(u[i],v[i]);
    if(op[i]=='+'){
      mp[{u[i],v[i]}]=i;
    }
    else{
      other[i]=mp[{u[i],v[i]}];
      other[mp[{u[i],v[i]}]]=i;
      mp.erase({u[i],v[i]});
    }
  }

  int id=k;
  for(auto p:mp){
    other[++id]=p.ss;
    other[p.ss]=id;
    u[id]=p.ff.ff,v[id]=p.ff.ss;
    op[id]='-';
  }
  ans=n;
  call(1,id);
}

signed main(){
  int t=1;
  //cin>>t;
  while(t--){
    solve();
  }
  return 0;
}
