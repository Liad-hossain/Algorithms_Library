const double EPS=1e-9; const int INF=2;//means inf sol
//returns how many solutions. ans has solutions
int gauss(vector<vector<double>>a,vector<double>&ans){
  int n = (int)a.size(); // number of equations
  int m = (int)a[0].size() - 1; // number of variables
  vector<int> where(m, -1); // solutions column
  for (int col=0, row=0; col<m && row<n; ++col) {
    int sel = row;
    for (int i=row; i<n; ++i)
    if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
    if (abs(a[sel][col]) < EPS) continue;
    for (int i=col; i<=m; ++i)
    swap(a[sel][i], a[row][i]);
    where[col] = row;
    for (int i=0; i<n; ++i)
    if (i != row) {
      double c = a[i][col] / a[row][col];
      for (int j=col; j<=m; ++j)
      a[i][j] -= a[row][j] * c;
    }
    ++row;
  }
  ans.assign(m, 0);
  for (int i=0; i<m; ++i)
  if (where[i] != -1)
  ans[i] = a[where[i]][m] / a[where[i]][i];
  for (int i=0; i<n; ++i) {
    double sum = 0;
    for (int j=0; j<m; ++j) sum += ans[j] * a[i][j];
    if (abs(sum - a[i][m]) > EPS) return 0;//no sol
  }
  for (int i=0; i<m; ++i)
  if (where[i] == -1) return INF; //inf solutions
  return 1; // has one solutions
}
