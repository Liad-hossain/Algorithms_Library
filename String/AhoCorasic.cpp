const int N=3e5+5;
const int LOG=26;
int to[N][LOG],nxt[N][LOG];
int dep[N],suffix_link[N];
int par[N],val[N];
int total_nodes=1;
vector<int> g[N]; // suffix_link tree
  int cnt[N];
  int add(string &s){
  int now=1;
  for(int i=0;i<(int)s.size();i++){
    int c=s[i]-'a';
    if(!to[now][c]){
      to[now][c]=(++total_nodes);
      par[total_nodes]=now;
      dep[total_nodes]=dep[now]+1;
      val[total_nodes]=c;
    }
    now=to[now][c];
  }
  return now;
}
void push_links(){
  queue<int> q;
  q.push(1);
  while(!q.empty()){
    int now=q.front();
    q.pop();
    if(dep[now]<=1){
      // ekhane hoy root na hoile single kno letter ase
      suffix_link[now]=1;
    }
    else{
      // just like kmp
      int sl=suffix_link[par[now]];
      int c=val[now];
      while(sl>1 and !to[sl][c])
      sl=suffix_link[sl];
      if(to[sl][c])
      sl=to[sl][c];
      suffix_link[now]=sl;
    }
    if(now!=1)
    g[suffix_link[now]].push_back(now);
    for(int i=0;i<LOG;i++)
    if(to[now][i])
    q.push(to[now][i]);
  }
}
// ekhane u node er sathe c character add korle
// tar suffix link ta ber korbo
// ekhane nxt array ta previous value save korar jnno
//rakhlam
// naile eki jinish barbar calculate hoite pare
int jump(int u, int c){
  if(nxt[u][c])
  return nxt[u][c];
  int v=u;
  while(v>1 and !to[v][c])
  v=suffix_link[v];
  if(to[v][c])
  v=to[v][c];
  return nxt[u][c]=v;
}
void solve(){
  ms(to,0);ms(nxt,0);ms(cnt,0);
  for(int i=0;i<N;i++)
  g[i].clear();
  total_nodes=1;
  dep[1]=0;
  int n;
  string t;
  cin>>n>>t;
  vector<string> s(n);
  vector<int> ans(n);
  for(int i=0;i<n;i++){
    cin>>s[i];
    ans[i]=add(s[i]);
  }
  push_links();
  int root=1;
  for(int i=0;i<(int)t.size();i++){
    int x=jump(root,t[i]-'a');
    cnt[x]++;
    root=x;
  }
  dfs(1);
  for(int i=0;i<n;i++){
  cout<<cnt[ans[i]]<<nl;
  }
}
