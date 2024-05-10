typedef vector<long long>col;
typedef vector<col>matrix;
long long Mod=1000000007;
//All the values should be long long
matrix operator*(const matrix &a,const matrix &b){
    long long n=a.size(),p=b.size(),m=b[0].size();
    matrix ans(n,col(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int k=0;k<p;k++){
            ans[i][j]=(ans[i][j]+a[i][k]*b[k][j])%Mod;
            }
        }
    }
    return ans;
}
matrix unit(long long n){
    matrix ans(n,col(n));
    for(int i=0;i<n;i++)ans[i][i]=1;
    return ans;
}
matrix power(matrix mat,long long p){
    if(p==0)return unit(mat.size());
    matrix ans=unit(mat.size());
    while(p){
        if(p&1)ans=ans*mat;
        mat=mat*mat;
        p>>=1;
    }
    return ans;
}
