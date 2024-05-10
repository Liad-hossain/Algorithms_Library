const int N=3e5+5;
int st[N][20];
int a[N],Log[N];
void precalc(int n){
    for(int i=2;i<=n;i++)Log[i]=Log[i/2]+1;
    for(int i=0;i<n;i++)st[i][0]=a[i];
    for(int j=1;j<=Log[n];j++){
        for(int i=0;i+(1<<j)<=n;i++){
            st[i][j]=__gcd(st[i][j-1],
            st[i+(1<<(j-1))][j-1]);
        }
    }
}
//O(1) query
int query(int l,int r){
    int len=r-l+1;
    int j=Log[len];
    return __gcd(st[l][j],st[r-(1<<j)+1][j]);
}

//O(logn) query
int query(int l,int r){
    int len=r-l+1;
    int g=0;
    while(len>0){
        g=__gcd(g,st[l][Log[len]]);
        l+=(1<<Log[len]);
        len-=(1<<Log[len]);
    }
    return g;
}