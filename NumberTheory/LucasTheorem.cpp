int small_nck(int n, int k,int p)
{
if (k < 0 || k > n) return 0;
return fact[n] * invf[k] % p * invf[n - k] % p;
}
int nck(int n,int r,int p)
{
if(r==0) return 1;int ni=n%p,ri=r%p;
return nck(n/p,r/p,p)*small_nck(ni,ri,p)%p;
}
int lucas(int n,int r,int p)
{
precompute(p); // binomial coeffiecient er ta
return nck(n,r,p);
}