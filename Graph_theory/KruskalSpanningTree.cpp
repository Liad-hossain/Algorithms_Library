struct spanning_tree{
  vector<int>par,rnk;
  spanning_tree(int n=0){
    par.resize(n+2),rnk.resize(n+2);
    for(int i=0;i<=n;i++){
      par[i]=-1,rnk[i]=1;
    }
  }
  int findpar(int a){
    if(par[a]==-1)return a;
    return par[a]=findpar(par[a]);
  }

  bool unite(int a,int b){
    a=findpar(a),b=findpar(b);
    if(a==b)return false;
    if(rnk[a]>rnk[b]){
      par[b]=a;
      rnk[a]+=rnk[b];
    }
    else{
      par[a]=b;
      rnk[b]+=rnk[a];
    }
    return true;
  }
};
