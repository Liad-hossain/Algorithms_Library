const int N=1e5+5;
vector<int>prime;
int fac[N];
void sieve(){
    fac[1]=1;
    for(int i=2;i<N;i++){
        if(!fac[i])prime.pb(i),fac[i]=i;
        for(int j=0;j<(int)prime.size() && i*prime[j]<N;j++){
            fac[i*prime[j]]=prime[j];
            if(i%prime[j]==0)break;
        }
    }
}