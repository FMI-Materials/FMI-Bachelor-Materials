#include <bits/stdc++.h>
 
using namespace std;
const int INF = 2e9;
 
struct Graph {
  // adj[i] este o lista de perechi (j, c) 
  // care reprezinta muchiile (i, j) de cost c
  int n;
  vector<vector<pair<int, int>>> adj;
  
  Graph(int n) : n(n), adj(n) {}
 
  void AddEdge(int a, int b, int c) {
    adj[a].emplace_back(b, c);
    // echivalent:
    //   adj[a].push_back(make_pair(b, c));
  }
  
  vector<int> Bellman(int src) {
    vector<int> dist(n, INF);
    dist[src] = 0;
    
    int changed = 1;
    while (changed--) {
      vector<int> new_dist(dist);
      for (int i = 0; i < n; ++i) {
        if (dist[i] == INF) continue;
        for (auto itr : adj[i]) {
          int j, cost; tie(j, cost) = itr;
          if (new_dist[j] > dist[i] + cost) {
            dist[j] = dist[i] + cost;
            changed = 1;
          }
        }
      }
    }
 
    for (int i = 0; i < n; ++i)
      if (dist[i] == INF)
        dist[i] = 0;
    return dist;
  }
};
 
int main() {
  ifstream cin("dijkstra.in");
  ofstream cout("dijkstra.out");
 
  int n, m; cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a; --b;
    graph.AddEdge(a, b, c);
  }
  vector<int> dist = graph.Bellman(0);
  for (int i = 1; i < n; ++i) 
    cout << dist[i] << " ";
  cout << endl;
 
  return 0;
}
