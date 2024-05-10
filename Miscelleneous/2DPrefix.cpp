void _2Ddiference(){
int n,m;
cin>>n>>m;
int a[n+1][m+1],dif[n+1][m+1];
ms(a,0);
ms(dif,0);
lp(i,1,n)
lp(j,1,m)
cin>>a[i][j];
lp(i,1,n){
lp(j,1,m){
dif[i][j]+=(a[i][j]);
dif[i][j]-=(a[i-1][j]+a[i][j-1]);
dif[i][j]+=(a[i-1][j-1]);
} }
int query;
cin>>query;
while(query--){
int x1,y1,x2,y2,num;
cin>>x1>>y1>>x2>>y2>>num;
dif[x1][y1]+=num;
dif[x1][y2+1]-=num;
dif[x2+1][y1]-=num;
dif[x2+1][y2+1]+=num;
}
ms(a,0);
/// new matrix
lp(i,1,n){
lp(j,1,m){
a[i][j]+=(a[i][j-1]+a[i-1][j]);
a[i][j]-=(a[i-1][j-1]);
a[i][j]+=dif[i][j];
} }
// print the matrix
}
// prefix
int que(int x1,int y1,int x2,int y2){
/// sum of the rectangle from (x1,y1) to (x2,y2)
int sum=0;
sum-=(pre[x1-1][y2] + pre[x2][y1-1]);
sum+=(pre[x1-1][y1-1]);
sum+=(pre[x2][y2]);
return sum;
}
void _2DPrefix(){
int n,m;
cin>>n>>m;
int a[n+1][m+1],pre[n+1][m+1];
ms(pre,0);
loop(i,1,n)loop(j,1,m)cin>>a[i][j];
loop(i,1,n){
loop(j,1,m){
pre[i][j]+=(pre[i][j-1]+pre[i-1][j]);
pre[i][j]-=(pre[i-1][j-1]);
pre[i][j]+=(a[i][j]);
}}}