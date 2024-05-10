const int N=105;
int prefer[2*N][N];
bool wprefersMoverM1(int w,int m,int m1,int n){
    for(int i=0;i<n;i++){
        if(prefer[w][i]==m)return true;
        if(prefer[w][i]==m1)return false;
    }
    return true;
}
vector<pair<int,int>>stable_marriage(int n){
    int wpartner[n+1];
    bool mfree[n+1];
    memset(wpartner,-1,sizeof(wpartner));
    for(int i=1;i<=n;i++)mfree[i]=1;
    int freecount=n;
    while(freecount>0){
        int m;
        for(m=1;m<=n;m++){
            if(mfree[m])break;
        }
        for(int i=0;i<n && mfree[m];i++){
            int w=prefer[m][i];
            if(wpartner[w-n]==-1){
                wpartner[w-n]=m;
                mfree[m]=false;
                freecount--;
            }
            else{
                int m1=wpartner[w-n];
                if(wprefersMoverM1(w,m,m1,n)){
                    wpartner[w-n]=m;
                    mfree[m]=false;
                    mfree[m1]=true;
                }
            }
        }
    }
    vector<pair<int,int>>partners;
    for(int i=1;i<=n;i++){
        partners.push_back({wpartner[i],i+n});
    }
    return partners;
}