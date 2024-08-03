#include <bits/stdc++.h>

using namespace std;

struct Graph {
  int n;
  vector<vector<int>> graph, trans;
  vector<int> vis, comp;
  vector<int> order;

  Graph(int n) : n(n), graph(n), trans(n), vis(n, 0), comp(n) {}

  void AddEdge(int a, int b) {
    graph[a].push_back(b);
    trans[b].push_back(a);
  }

  void DFS1(int node) {
    vis[node] = 1;
    for (auto nei : graph[node]) {
      if (!vis[nei]) {
        DFS1(nei);
      }
    }
    order.push_back(node);
  }

  void DFS2(int node, int scc_id) {
    vis[node] = true;
    comp[node] = scc_id;
    for (auto nei : trans[node]) {
      if (!vis[nei]) {
        DFS2(nei, scc_id);
      }
    }
  }

  vector<int> ComputeSCC() {
    for (int i = 0; i < n; ++i)
      if (!vis[i])
        DFS1(i);
    
    // "trucul" push_front -> push_back + reverse la final.
    assert((int)order.size() == n);
    reverse(order.begin(), order.end());
    fill(vis.begin(), vis.end(), 0);
    
    int scc_count = 0;
    for (auto i : order) {
      if (!vis[i]) {
        DFS2(i, scc_count);
        scc_count++;
      }
    }

    return comp;
  }
};


int main() {
  int n, m; cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    // presupun 0 <= a, b < n
    int a, b; cin >> a >> b; 
    graph.AddEdge(a, b);
  }
  
  // Functie care calculeaza ctc
  // pt fiecare nod i calculeaza comp[i]
  // indexul comp tare conexe
  vector<int> comp = graph.ComputeSCC();
  
  for (int i = 0; i < n; ++i)
    cout << comp[i] << " ";
  cout << '\n';

  return 0;
}
