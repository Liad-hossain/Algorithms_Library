const int N=2e5+5;
vector<int>st[4*N];
int a[N];
void build(int si,int ss,int se){
    st[si].clear();
    if(ss==se){
        st[si].pb(a[ss]);
        return;
    }

    int mid=(ss+se)/2;
    build(2*si,ss,mid);
    build(2*si+1,mid+1,se);
    int l=0,r=0;
    while(l<(int)st[2*si].size() && r<(int)st[2*si+1].size()){
        if(st[2*si][l]<st[2*si+1][r])
          st[si].pb(st[2*si][l]),l++;
        else st[si].pb(st[2*si+1][r]),r++;
    }

    while(l<st[2*si].size())st[si].pb(st[2*si][l]),l++;
    while(r<st[2*si+1].size())st[si].pb(st[2*si+1][r]),r++;
}
int query(int si,int ss,int se,int l,int r,int val){
    if(ss>r || se<l)return 0;
    if(ss>=l && se<=r){
        int lo=0,hi=(int)st[si].size()-1,id=-1;
        while(lo<=hi){
            int m=(lo+hi)/2;
            if(st[si][m]>val)id=m,hi=m-1;
            else lo=m+1;
        }

        if(id==-1)return 0;
        int n=st[si].size();
        return n-id;
    }

    int mid=(ss+se)/2;
    return query(2*si,ss,mid,l,r,val)+
          query(2*si+1,mid+1,se,l,r,val);
}
