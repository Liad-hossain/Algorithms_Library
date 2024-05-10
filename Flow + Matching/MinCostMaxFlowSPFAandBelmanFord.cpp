///Complexity using Bellman Ford min(VE*VE,F*VE)
///Complexity using SPFA min(VE*E,F*E), F=Flow
///It is avergare for SPFA, in worst=Bellman
#define INF 5e18
#define eps 1e-9
using T=long long;
struct Edge {
    int from, to;
    T cap, flow;
    T cost;
};
const int MX=100005;
struct MCMF {//0-indexed
    int n, m, s, t;
    vector<Edge> edges;
    vector<vector<int>> G;
    vector<int> p;
    int inq[MX];
    vector<T> d, a;
    void init(int maxn,int source,int sink) {
        G.resize(maxn,vector<int>(maxn));
        p.resize(maxn);
        d.resize(maxn);
        a.resize(maxn);
        n=maxn,s=source,t=sink;
        for(int i = 0; i < n; i++) G[i].clear();
        edges.clear();
    }
    void AddEdge(int from,int to,T cap,T cost) {
        edges.push_back((Edge){from, to, cap, 0, cost});
        edges.push_back((Edge){to, from, 0, 0, -cost});
        m = edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    pair<T,T> Mincost() {//bellmanFord
        T tot_cost = 0;
        T tot_flow = 0;
        while(true) {
            for(int i = 0; i < n; i++) d[i] = INF;
            d[s] = 0;
            p[s] = 0;
            a[s] = INF;
            bool up=true;
            while(up) {
                up=false;
                for(int u = 0; u < n; u++) {
                    if(d[u]-INF>=-eps)continue;
                    for(int j:G[u]) {
                        Edge &e=edges[j];
                        if(e.cap>e.flow && d[e.to]>d[u]+e.cost+eps){
                            d[e.to] = d[u] + e.cost;
                            p[e.to] = j;
                            a[e.to]=min(a[u],e.cap-e.flow);
                            up=true;
                        }
                    }
                }
            }
            if(abs(d[t]-INF)<=eps)break;
            tot_cost += (T)d[t] * a[t];
            tot_flow += (T)a[t];
            int u = t;
            while(u != s) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
                u = edges[p[u]].from;
            }
        }
        return {tot_cost,tot_flow};
    }
    pair<T,T> Mincost2() {//SPFA
        T tot_cost = 0;
        T tot_flow = 0;
        while(true) {
            for(int i = 0; i < n; i++) d[i] = INF;
            memset(inq, 0, sizeof(inq));
            d[s] = 0;
            inq[s] = 1;
            p[s] = 0;
            a[s] = INF;
            queue<int> Q;
            srand(time(NULL));
            Q.push(s);
            while(!Q.empty()) {
                int u = Q.front();
                Q.pop();
                inq[u] = 0;
                for(int i = 0; i < G[u].size(); i++) {
                    Edge& e = edges[G[u][i]];
                    if(e.cap > e.flow && d[e.to] > d[u] + e.cost+eps) {
                        d[e.to] = d[u] + e.cost;
                        p[e.to] = G[u][i];
                        a[e.to] = min(a[u], e.cap - e.flow);
                        if(!inq[e.to]) {
                            Q.push(e.to);
                            inq[e.to] = 1;
                        }
                    }
                }
            }
            if(abs(d[t]-INF)<=eps)break;
            tot_cost += (T)d[t] * a[t];
            tot_flow += a[t];
            int u = t;
            while(u != s) {
                edges[p[u]].flow += a[t];
                edges[p[u]^1].flow -= a[t];
                u = edges[p[u]].from;
            }
        }
        return {tot_cost,tot_flow};
    }
};
