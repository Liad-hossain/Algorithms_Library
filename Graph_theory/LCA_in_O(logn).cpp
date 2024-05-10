const int N=1e5+5;
namespace LCA{
    vector<pair<int, int>> g[N];
    int level[N], Log[N], Lca[N][25];
    int _N;

    void init(int n){
        _N = n;
        for (int i = 1; i <= n; i++)
            g[i].clear();
        for (int i = 1; i <= n; i++){
            for (int j = 0; j < 24; j++)
                Lca[i][j] = -1;
        }
    }
    void addEdge(int u, int v, int w = 1){
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    void dfs(int node, int par, int lvl){
        Lca[node][0] = par;
        level[node] = lvl;
        for (pair<int, int> child : g[node]){
            if (child.first == par)
                continue;
            dfs(child.first, node, lvl + 1);
        }
    }
    void calc(){
        dfs(1, -1, 0);
        Log[1] = 0;
        for (int i = 2; i <= _N; i++)
            Log[i] = Log[i / 2] + 1;
        for (int j = 1; j < 23; j++){
            for (int i = 1; i <= _N; i++){
                int par = Lca[i][j - 1];
                if (par != -1){
                    Lca[i][j] = Lca[par][j - 1];
                }
            }
        }
    }
    int lca(int a, int b){
        if (level[a] > level[b])
            swap(a, b);
        int d = level[b] - level[a];

        while (d > 0){
            int i = Log[d];
            b = Lca[b][i];
            d -= (1 << i);
        }

        if (a == b)
            return a;
        for (int i = 22; i >= 0; i--){
            if (Lca[a][i] != -1 && Lca[a][i] != Lca[b][i]){
                a = Lca[a][i], b = Lca[b][i];
            }
        }
        return Lca[a][0];
    }
}
