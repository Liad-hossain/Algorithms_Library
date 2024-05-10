const int ln = 10,N=1005 ;
int rmq[N][N][ln][ln];
int n , m , a[N][N],Log[N];
/// a is the given matrix 1 based index

void preprocess () {
    FOR(i,N) {
        int j = 0 ;
        while(1<<(j+1)<=i) j++;
        Log[i] = j;
    }
    FOR(i,ln) {
        FOR(j,ln) {
            F0R(x,n) {
                if (x+(1<<i)-1>n) break;
                F0R(y,m) {
                    if (y+(1<<j)-1>m) break;
                    if (i==0 and j==0) {
                        rmq[x][y][0][0] = a[x][y] ;
                    }
                    else if (i==0) {
                        int yh = y + (1<<(j-1)) ;
                        rmq[x][y][0][j] = max(rmq[x][y][0][j-1],rmq[x][yh][0][j-1]) ;
                    }
                    else if (j==0) {
                        int xh = x + (1<<(i-1)) ;
                        rmq[x][y][i][0] = max(rmq[x][y][i-1][0],rmq[xh][y][i-1][0]) ;
                    }
                    else {
                        int xh = x + (1<<(i-1)) , yh = y + (1<<(j-1)) ;
                        rmq[x][y][i][j] = max(rmq[x][y][i][j-1],rmq[x][yh][i][j-1]) ;
                    }
                }
            }
        }
    }
}
/// gives maximum of matrix with upper left point (x1,y1) and lower right point (x2,y2)
int query(int x1,int y1,int x2,int y2) {        
    int lx = x2-x1+1 , ly = y2-y1+1 , kx = 0 , ky = 0;
    kx = Log[lx] , ky = Log[ly] ;
    x2 = x2+1-(1<<kx) , y2 = y2+1-(1<<ky) ;
    return max({rmq[x1][y1][kx][ky],rmq[x1][y2][kx][ky],rmq[x2][y1][kx][ky],rmq[x2][y2][kx][ky]}) ;
}