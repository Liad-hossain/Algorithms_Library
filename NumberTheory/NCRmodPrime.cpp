const int N=1e5+5;
#define mod 1000000007
int fac[N],inv[N];
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1)res=(res*a)%mod;
        n/=2;
        a=(a*a)%mod;
    }

    return res;
}

void pre(){
    fac[0]=1;
    for(int i=1;i<N;i++){
        fac[i]=(fac[i-1]*i)%mod;
    }
    inv[N-1]=power(fac[N-1],mod-2);
    for(int i=N-2;i>=0;i--){
        inv[i]=(inv[i+1]*(i+1))%mod;
    }
}

int ncr(int n,int r){
    int res=fac[n];
    res=(res*inv[r])%mod;
    res=(res*inv[n-r])%mod;
    return res;
}