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

  vector<int> Dijkstra(int src) {
    vector<int> dist(n, 0);
    vector<bool> vis(n, false);
    // pereche {timp, nod}
    priority_queue<pair<int, int>> pq;
    
    // echivalent:
    //   priority_queue<
    //     pair<int, int>,
    //     vector<pair<int, int>>, 
    //     greater<pair<int, int>>
    //   > pq;

    // pornim "bfs"-ul din src
    pq.emplace(0, src);

    // Simulam "bfs"-ul
    while (!pq.empty()) {
      // Iau evenimentul care se intampla cel mai devreme
      int at, node; 
      tie(at, node) = pq.top(); 
      pq.pop();
      at = -at;
      
      // -----v
      if (vis[node]) continue;
      vis[node] = true;
      // -----^

      // INV:  se ruleaza maxim o data pt fiecare node 
      dist[node] = at;
      for (auto itr : adj[node]) {
        // INV: se ruleaza maxim o data pt fiecare muchie
        int nei, cost; tie(nei, cost) = itr;
        // adaugam noile evenimente.
        pq.emplace(-(at + cost), nei);
      }
    }

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
  vector<int> dist = graph.Dijkstra(0);
  for (int i = 1; i < n; ++i) 
    cout << dist[i] << " ";
  cout << endl;

  return 0;
}
