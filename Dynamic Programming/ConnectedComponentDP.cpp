///Count the number of permutations of len n
int call(int n){
  int dp[n+1][n+1];
  memset(dp,0,sizeof(dp));
  dp[0][0]=1;
  for(int i=1;i<=n;i++){
    ///we are making j components with i elements
    for(int j=1;j<=n;j++){
      ///we can create a new component
      ///place this new component between any two existing components
      ///before the first one and after the last one
      ///There are j places with j-1 components
      dp[i][j]+=dp[i-1][j-1]*j;

      ///we can add the number at the begining or end of any existing components
      ///so with j components there are 2*j places
      dp[i][j]+=dp[i-1][j]*(2*j);

      ///we can merge two components by placing at the end of a component and
      /// at the begining of the next component at the same time
      /// So we are making j components from j+1 components
      /// There are j choices for j+1 components
      dp[i][j]+=dp[i-1][j+1]*j;
    }
  }
  ///Final answer will be dp[n][1], because all the number should be in one component
  return dp[n][1];
}
