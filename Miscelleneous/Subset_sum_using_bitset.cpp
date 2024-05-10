vector<int>vals;
template<int N = 1>
int subset_sum(int S) {
  if (N < S) {
    return subset_sum<min((int) 1e6, 2 * N)> (S);
  }
  bitset<N> dp;
  dp[0] = 1;
  for (int i : vals) dp |= dp << i;
  for (int i = S / 2; i >= 0; i--) {
    if (dp[i]) return i;
  }
}
void get(vector<int> v, int S) {
  if (v.empty()) return;
  multiset<int> st;
  for (int i : v) st.insert(i);
  vals.clear();
  while (st.size() > 2) {
    int a = *st.begin();
    int b = *next(st.begin());
    int c = *next(next(st.begin()));
    if (a == c) {
      st.erase(st.begin());
      st.erase(st.begin());
      st.insert(2 * a);
    } else {
      vals.push_back(a);
      st.erase(st.begin());
    }
  }
  for (int i : st) vals.push_back(i);
  int x = subset_sum(S);
}