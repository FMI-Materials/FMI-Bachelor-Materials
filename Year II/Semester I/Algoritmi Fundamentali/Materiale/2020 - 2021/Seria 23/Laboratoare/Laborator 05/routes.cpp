#include <bits/stdc++.h>

using namespace std;

struct Graph {
  int n, src, dst;
  // edge is pair (neighbor, color)
  // color == 0 ==> BLACK (graph edge)
  // color == 1 ==> RED   (solution edge)
  vector<vector<pair<int, int>>> adj;
  vector<bool> vis;

  Graph(int n) : n(n), adj(n), vis(n) {}
  
  void AddEdge(int a, int b) {
    adj[a].emplace_back(b, 0);
  }
  
  bool dfs(int node) {
    if (vis[node]) return false;
    if (node == dst) return true;
    vis[node] = true;

    for (int i = 0; i < (int)adj[node].size(); ++i) {
      auto [nei, col] = adj[node][i];
      bool found = dfs(nei);
      if (!found) continue;
      
      adj[nei].emplace_back(node, !col);
      // stergem muchia node -> nei
      // adj[node].erase(adj[node].begin() + i);
      swap(adj[node][i], adj[node].back());
      adj[node].pop_back();

      return true;
    }
    return false;
  }

  bool dfs2(int node, vector<int>& path) {
    if (vis[node]) return false;
    if (node == src) {
      path.push_back(node);
      return true;
    }
    vis[node] = true;
    
    for (int i = 0; i < (int)adj[node].size(); ++i) {
      auto [nei, col] = adj[node][i];
      if (col == 0) continue;
      bool found = dfs2(nei, path);
      if (!found) continue;
      
      adj[node][i].second = 0;
      // adj[nei].emplace_back(node, !col);
      // stergem muchia node -> nei
      // adj[node].erase(adj[node].begin() + i);
      // swap(adj[node][i], adj[node].back());
      // adj[node].pop_back();
      path.push_back(node);
      return true;
    }
    return false;
  }

  vector<vector<int>> FordFulkerson(int src, int dst) {
    this->src = src; this->dst = dst;
    int max_flow = 0;
    while (true) {
      fill(vis.begin(), vis.end(), 0);
      if (!dfs(src)) break;
      max_flow += 1;
    }
    vector<vector<int>> paths(max_flow);
    for (int i = 0; i < max_flow; ++i) {
      fill(vis.begin(), vis.end(), 0);
      assert(dfs2(dst, paths[i]));
    }
    return paths;
  }
};

int main() {
  int n, m; cin >> n >> m;
  Graph G(n);
  for (int i = 0; i < m; ++i) {
    int a, b; cin >> a >> b; --a; --b;
    G.AddEdge(a, b);
  }

  auto answer = G.FordFulkerson(0, n - 1);
  cout << answer.size() << '\n';
  for (auto path : answer) {
    cout << path.size() << '\n';
    for (auto node : path) 
      cout << node + 1 << " ";
    cout << '\n';
  }

  return 0;
}
