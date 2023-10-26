#include <bits/stdc++.h>

using namespace std;

struct Graph {
  int n, src, dst;
  // edge is pair (neighbor, color)
  // color == 0 ==> BLACK (graph edge)
  // color == 1 ==> RED   (solution edge)
  vector<vector<long long>> cap;
  vector<vector<int>> adj;

  Graph(int n) : n(n), adj(n), 
      cap(n, vector<long long>(n, 0)) {}
  
  void AddEdge(int a, int b, int c) {
    adj[a].push_back(b);
    adj[b].push_back(a);
    cap[a][b] += c;
    // cap[b][a] == 0
  }
  
  int ek_iter() {
    vector<bool> vis(n, false);
    vector<int> parent(n, -1);

    vector<int> q;
    auto push = [&](int node, int par) {
      if (vis[node]) return;
      vis[node] = true;
      parent[node] = par;
      q.push_back(node);
    };

    push(src, -1);
    for (int i = 0; i < (int)q.size(); ++i) {
      int node = q[i];
      for (auto nei : adj[node]) {
        if (cap[node][nei] > 0)
          push(nei, node);
      }
    }

    if (parent[dst] == -1) 
      return 0;

    long long flow = 2e18;
    for (int node = dst; node != src; node = parent[node]) 
      flow = min(flow, cap[parent[node]][node]);
    assert(flow > 0);

    for (int node = dst; node != src; node = parent[node]) {
      cap[parent[node]][node] -= flow;
      cap[node][parent[node]] += flow;
    }
    return flow;
  }

  long long FordFulkerson(int src, int dst) {
    this->src = src; this->dst = dst;
    long long max_flow = 0;
    while (true) {
      long long curr_flow = ek_iter();
      if (curr_flow == 0) break;
      max_flow += curr_flow;
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
