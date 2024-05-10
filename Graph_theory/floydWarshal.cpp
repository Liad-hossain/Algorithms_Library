const int N=505;
#define INF 1e18
struct floydWarshal{
  long long int dist[N][N];
  floydWarshal(int n=0){
    for(int i=1;i<=n;i++){
      for(int j=1;j<=n;j++)dist[i][j]=INF;
      dist[i][i]=0;
    }
  }

  bool apply(int n){
    for(int k=1;k<=n;k++){
      for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
          if(dist[i][k]!=INF && dist[k][j]!=INF){
            dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
          }
        }
      }
    }

    for(int i=1;i<=n;i++){
      if(dist[i][i]!=0)return false;
    }

    return true;
  }
};
