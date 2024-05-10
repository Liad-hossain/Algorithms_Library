#define inf 9000000000000000000

struct dijkstra{
  vector<vector<pair<int,int>>>graph;
  vector<long long int>dist;

  dijkstra(int n=0)
  {
    graph.resize(n+5);
    dist.resize(n+5);
    for(int i=1;i<=n;i++)
    {
      graph[i].clear();
      dist[i]=inf;
    }
  }

  void apply(int node)
  {
    priority_queue<pair<long long int,int>>pq;
    pq.push({0,node});
    dist[node]=0;

    while(!pq.empty())
    {
      int cur=pq.top().second;
      long long int w=-pq.top().first;
      pq.pop();

      if(dist[cur]<w)continue;

      for(auto child:graph[cur])
      {
        if(dist[cur]+child.second<dist[child.first])
        {
          dist[child.first]=dist[cur]+child.second;
          pq.push({-dist[child.first],child.first});
        }
      }
    }
  }
};
