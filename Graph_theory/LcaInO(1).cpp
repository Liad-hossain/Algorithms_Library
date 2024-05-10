const int N=2e5+4,LOG=23;
namespace LCA{
    int sum[N] ;
    int st[N] , en[N] , lg[N] , par[N] , a[N] , id[N] , dp[LOG][N] ;
    vector <int>g[N] ;
    int n , r , Time , cur ;
    void init(int nodes, int root){
        n = nodes, r = root, lg[0] = lg[1] = 0;
        for (int i = 2; i <= n; i++) lg[i] = lg[i >> 1] + 1;
        for (int i = 0; i <= n; i++) g[i].clear();
    }
    void addEdge(int u, int v){
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int lca(int u, int v)
    {
        if( en[u] > en[v] )swap(u,v) ;
        if( st[v] <= st[u] && en[u] <= en[v] ) return v ;
        int l = lg[id[v] - id[u] + 1] ;
        int p1 = id[u] , p2 = id[v] - (1<<l) + 1 ;
        if( sum[ dp[l][p1] ] < sum[ dp[l][p2] ] ) return par[dp[l][p1]] ;
        else return par[ dp[l][p2] ] ;
    }
    int dis( int u ,int v )
    {
        int l = lca(u,v) ;
        return (sum[u] + sum[v] - ( sum[l]<<1LL )) ;
    }
    void dfs(int u, int p , int curSum){
        st[u] = ++Time ; par[u] = p ; sum[u] = curSum ;
        for(int i=0 ; i<g[u].size() ; i++)
        {
            if( g[u][i]==p ) continue ;
            dfs( g[u][i] ,u,curSum+1) ;
        }
        en[u] = ++Time ;
        a[++cur] = u ;
        id[u] = cur ;
    }
    // returns 1 if u is an anc of v
    bool anc(int u, int v){
        return st[u] <= st[v] && en[u] >= en[v];
    }
    void build(){
        cur = Time = 0 ;
        dfs( r , r , 0 );
        for(int i=1 ; i<=n ; i++)dp[0][i]=a[i] ;
        for(int l=0 ; l<LOG-1 ; l++){
            for(int i=1 ; i<=n ; i++){
                dp[l+1][i] = dp[l][i] ;
                if( (1<<l)+i <= n && sum[dp[l][i+(1<<l)]] < sum[dp[l][i]]) dp[l+1][i] = dp[l][ i+(1<<l)] ;
            }
        }
    }
}
