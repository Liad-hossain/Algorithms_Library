//Based on problem "Group Projects" of CF
int dp[203][203][1003]
int call(){
    //Open and close interval trick
    dp[0][0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=n;j++){
            for(int im=0;im<=k;im++){
                int v=dp[i-1][j][im];
                int val=im+j*(a[i]-a[i-1]);
                if(val>k)continue;
                //create own group
                dp[i][j][val]=(dp[i][j][val]+v)%mod;

                //create a new group
                dp[i][j+1][val]=(dp[i][j+1][val]+v)%mod;

                //insert one of the jth group and don't close
                dp[i][j][val]=
                (dp[i][j][val]+(v*1LL*j)%mod)%mod;

                //insert one of the jth group and close it
                if(j-1<0)continue;
                dp[i][j-1][val]=
                (dp[i][j-1][val]+(v*1LL*j)%mod)%mod;
            }
        }
    }
    int ans=0;
    for(int i=0;i<=k;i++)ans=(ans+dp[n][0][i])%mod;
    return ans;
}
