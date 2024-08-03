#include <bits/stdc++.h>

using namespace std;

struct Graph {
  int n, src, dst;
  // edge is pair (neighbor, color)
  // color == 0 ==> BLACK (graph edge)
  // color == 1 ==> RED   (solution edge)
  vector<vector<long long>> cap;
  vector<vector<int>> adj;
  vector<bool> vis;

  Graph(int n) : n(n), adj(n), 
      vis(n), cap(n, vector<long long>(n, 0)) {}
  
  void AddEdge(int a, int b, int c) {
    adj[a].push_back(b);
    adj[b].push_back(a);
    cap[a][b] += c;
    // cap[b][a] == 0
  }
  
  bool dfs(int node, vector<int>& path) {
    if (vis[node]) return false;
    if (node == dst) {
      path.push_back(node);
      return true;
    }
    vis[node] = true;

    for (auto nei : adj[node]) {
      if (cap[node][nei] == 0) continue;
      bool found = dfs(nei, path);
      if (!found) continue;
      path.push_back(node);
      return true;
    }
    return false;
  }

  long long FordFulkerson(int src, int dst) {
    this->src = src; this->dst = dst;
    long long max_flow = 0;
    vector<int> path;
    while (true) {
      fill(vis.begin(), vis.end(), 0);
      path.clear();
      if (!dfs(src, path)) break;
      // push flow on path
      reverse(path.begin(), path.end());
      long long curr_flow = cap[path[0]][path[1]];
      for (int i = 1; i < (int)path.size(); ++i) 
        curr_flow = min(curr_flow, cap[path[i - 1]][path[i]]);

      max_flow += curr_flow;
      // "inversez muchiile"
      for (int i = 1; i < (int)path.size(); ++i) {
        cap[path[i - 1]][path[i]] -= curr_flow;
        cap[path[i]][path[i - 1]] += curr_flow;
      }
    }
    return max_flow;
  }
};

int main() {
  ifstream cin("maxflow.in");
  ofstream cout("maxflow.out");

  int n, m; cin >> n >> m;
  Graph G(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a; --b;
    G.AddEdge(a, b, c);
  }

  auto answer = G.FordFulkerson(0, n - 1);
  cout << answer << '\n';

  return 0;
}
