struct BIT { //1-indexed
  int n; vector<int> t;
  BIT() {}
  BIT(int _n) {
    n = _n; t.assign(n + 1, 0);
  }
  // point update, range query
  void upd(int i, int val) {
    if(i <= 0) return;
    for(;i<=n;i+=(i&-i))t[i]+=val;
  }
  int query(int l, int r) {
    return query(r)-query(l - 1);
  }
  // range update, point query
  void upd(int l, int r, int val) {
    upd(l, val);
    upd(r + 1, -val);
  }
  int query(int i){
    int ans = 0;
    for (; i >= 1; i -= (i & -i)) ans += t[i];
    return ans;
  }
};
// range update, range query
const int MAXN = 1000005;
int BIT[2][MAXN];
void update(int cs, int indx, int val){
  while(indx < MAXN){
    BIT[cs][indx] += val;
    indx += (indx & -indx);
  }
}
int sum(int cs, int indx){
  int ans = 0;
  while(indx != 0) {
    ans += BIT[cs][indx];
    indx -= (indx & -indx);
  }
  return ans;
}
void updateRange(int l, int r, int val){
  update(0,l,val); update(0,r+1,-val);
  update(1,l,val*(l-1)); update(1,r+1,-val*r);
}
int sumRange(int indx){
  return sum(0,indx)*indx - sum(1,indx);
}
int QueryRange(int l, int r){
  return sumRange(r)-sumRange(l-1);
}
