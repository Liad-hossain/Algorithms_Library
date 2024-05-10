int ncr(int n,int r){
    if(r>n)return 0;
    int res=1;
    for(int i=1;i<=r;i++){
        res=res*(n-i+1);
        res/=i;
    }
    return res;
}