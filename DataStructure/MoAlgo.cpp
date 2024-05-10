const int N = 2e5 + 5;
struct query{
  int SQRT = 500;
  int l, r, id;
  bool operator< (query b){
    query a = *this;
    return array<int,2>{a.l/SQRT,a.r} <
    array<int,2>{b.l/SQRT,b.r};
  }
};
query qs[N];
void mo_algo() {
  sort(qs+1,qs+q+1);
  int curL=1, curR=0;
  for(int i=1;i<=q;i++) {
    int L = qs[i].l, R = qs[i].r;
    while(curR < R) add(++curR);
    while(curL > L) add(--curL);
    while(curR > R) subtract(curR--);
    while(curL < L) subtract(curL++);
    ans[qs[i].id] = cur;
  }
}
