///Complexity O(V*E^2)
#define INF 7e18
using T=long long;
struct Edmonds_Carp{
  vector<int> parent;
  // represents the graph and it may contain negative edges
  vector<vector<T>> graph,capacity,flowPassed;
  Edmonds_Carp(int n){
    parent.resize(n+5);
    graph.resize(n+5);
    flowPassed.resize(n+5,vector<T>(n+5));
    capacity.resize(n+5,vector<T>(n+5));
  }
  T bfs(int s, int t) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, T>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        T flow = q.front().second;
        q.pop();
        for(int next : graph[cur]){
          if(parent[next]==-1 &&
          capacity[cur][next]-flowPassed[cur][next]>0){
              parent[next]=cur;
              T new_flow=min(flow,capacity[cur][next]-
                flowPassed[cur][next]);
              if (next == t)
                  return new_flow;
              q.push({next, new_flow});
          }
        }
    }
    return 0;
  }
  //For directed edge set directed=true
  void AddEdge(int u,int v,T w,bool directed){
    capacity[u][v] = w;
    if(!directed)capacity[v][u]=w;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }
  T max_flow(int source, int sink){
    T maxFlow = 0;
    while(1) {
      //ind an augmented path and max flow corresponding to it
      T flow = bfs(source, sink);
      // if no path available, flow will be 0
      if(flow==0)
          break;
      int u = sink;
      maxFlow += flow;
  // we update the passed flow matrix
      while(u != source)
      {
          int v = parent[u];
          flowPassed[v][u] += flow;
          flowPassed[u][v] -= flow;
          u=v;
      }
    }
    return maxFlow;
  }

};
