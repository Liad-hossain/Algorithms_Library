// n=1e12,sqrt(n)
int sum(int n)
{int ans=(n*(n+1)%mod)*inverse(2)%mod;return ans;}
int divisorsum(int n){
int left=1;int ans=0;
while(left<=n){int k=n/left;int right=n/k;
ans=(ans+((sum(right)-sum(left-1)))*k);
left=right+1;}return ans%mod;
}