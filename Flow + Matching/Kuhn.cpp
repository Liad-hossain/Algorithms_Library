//1-indexed. Left and Right independently numbered.
//ml, mr contain matches for left and right parts.
namespace Kuhn {
    const int maxN = 1e5+7, maxM = 1e5+7;     ///Check
    int n, m, match;
    int vis[maxN], level[maxN], ml[maxN], mr[maxM];
    vector<int> edge[maxN];   /// constructing edges for left part only

    void init(int N, int M) {      /// N = nodes in left part, M = nodes in right part
        n = N, m = M;
        for (int i=1; i<=n; i++)    edge[i].clear(), ml[i] = -1;
        for (int i=1; i<=m; i++)    mr[i] = -1;
        match = 0;
    }

    void add(int u, int v) {
        edge[u].push_back(v);
        if (ml[u] == -1 && mr[v] == -1)     ml[u] = v, mr[v] = u, match++;
    }

    bool dfs(int u) {
        vis[u] = true;
        for (int x: edge[u]) {
            int v = mr[x];
            if (v == -1 || (!vis[v] && dfs(v))) {
                ml[u] = x; mr[x] = u;
                return true;
            }
        }
        return false;
    }

    int matching() {
        while (true) {
            for (int i = 1; i <= n; ++i) {
                if (ml[i] == -1)    level[i] = 0;
                else                level[i] = -1;
            }

            for (int i = 1; i <= n; ++i) vis[i] = false;
            int d = 0;
            for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
            if (d == 0) return match;
            match += d;
        }
    }
}