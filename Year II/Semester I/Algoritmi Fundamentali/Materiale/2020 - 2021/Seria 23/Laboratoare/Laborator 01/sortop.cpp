#include <bits/stdc++.h>

using namespace std;

void DFS(int node, vector<vector<int>>& graph, 
    vector<int>& order, vector<int>& vis) {
  // vis[node] = 
  // 0, daca nu e inca procesat
  // 1, daca e in procesare
  // 2, daca a fost terminat de procesat
  vis[node] = 1;
  for (auto nei : graph[node]) {
    if (vis[nei] == 1) {
      // CICLUL: din parent in parent de la node la nei
      cerr << "ERROR: Exista ciclu" << endl;
      exit(42);
    }
    if (!vis[nei]) {
      // parent[vec] = node;
      DFS(nei, graph, order, vis);
    }
  }
  vis[node] = 2;
  order.push_back(node);
}

int main() {
  int n, m; cin >> n >> m;
  vector<vector<int>> graph(n);
  for (int i = 0; i < m; ++i) {
    // pp 0 <= a, b < n
    int a, b; cin >> a >> b; 
    graph[a].push_back(b);
  }

  // order va mentine sortarea topologica
  vector<int> order;
  // vis va contoriza daca un nod e vizitat sau nu
  vector<int> vis(n, 0);

  for (int i = 0; i < n; ++i) {
    if (!vis[i]) {
      DFS(i, graph, order, vis);
    }
  }
  reverse(order.begin(), order.end());

  for (auto node : order) 
    cout << node << " ";
  cout << '\n';

  return 0;
}
