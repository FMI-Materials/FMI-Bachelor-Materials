#include <bits/stdc++.h>

using namespace std;
const int INF = 2e9;

struct Graph {
  // adj[i] este o lista de perechi (j, c) 
  // care reprezinta muchiile (i, j) de cost c
  int n;
  vector<tuple<int, int, int>> edges;
  
  Graph(int n) : n(n) {}

  void AddEdge(int a, int b, int c) {
    edges.emplace_back(a, b, c);
    // echivalent:
    //   adj[a].push_back(make_pair(b, c));
  }
  
  vector<int> Bellman(int src) {
    vector<int> dist(n, INF);
    dist[src] = 0;
    
    // EXPERIMENT: Ce ordine ar fi buna de ales?
    // (wikipedia are o pagina despre asta)
    sort(edges.begin(), edges.end(), 
        [&](tuple<int, int, int> e1, tuple<int, int, int> e2) {
      int a1, b1, c1; tie(a1, b1, c1) = e1;
      int a2, b2, c2; tie(a2, b2, c2) = e2;
      // a < b primele, sortate dupa a
      // a > b ultimele, sortate dupa -a
      if ((a1 < b1) != (a2 < b2)) 
        return a1 < b1;
      if (a1 < b1) return a1 < a2;
      return a1 > a2;
    });
    
    int changed = 1;
    while (changed--) {
      // e foarte dependent de ordinea in care procesez
      // nodurile/muchiile
      for (auto itr : edges) {
        int i, j, cost; tie(i, j, cost) = itr;
        if (dist[i] != INF && dist[j] > dist[i] + cost) {
          dist[j] = dist[i] + cost;
          changed = 1;
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
