#include <bits/stdc++.h>

using namespace std;

struct DS {
  int n;
  vector<int> color, cnt;
  vector<vector<int>> adj;

  DS(int n) : n(n), color(n), cnt(n, 1), adj(n) {
    for (int i = 0; i < n; ++i)
      color[i] = i;
  }

  bool Connected(int a, int b) {
    // BFS(a)
    return color[a] == color[b];
  }

  void dfs(int node, int col) {
    color[node] = col;
    cnt[col]++;

    for (auto vec : adj[node]) {
      if (color[vec] != col) {
        dfs(vec, col);
      }
    }
  }

  void Link(int a, int b) {
    // adaugam muchia a, b
    // 1. recoloram
    if (cnt[color[a]] < cnt[color[b]]) {
      cnt[color[a]] = 0;
      dfs(a, color[b]);
    } else {
      cnt[color[b]] = 0;
      dfs(b, color[a]);
    }
    // 2. adaugam muchia
    adj[a].push_back(b);
    adj[b].push_back(a);
  }
};

struct Graph {
  struct Edge {
    int a, b, c; 
    Edge(int a, int b, int c) : a(a), b(b), c(c) {}
    
    bool operator<(const Edge& oth) const {
      return c < oth.c;
    }
  };

  int n;
  vector<Edge> edges;
  vector<Edge> mst_edges;

  Graph(int n) : n(n) {}

  void AddEdge(int a, int b, int c) {
    edges.emplace_back(a, b, c);
  }

  long long ComputeMST() {
    // 1. sortam muchiile.
    sort(edges.begin(), edges.end());

    // 2. pentru fiecare muchie in ordine,
    DS ds(n);
    long long answer = 0;
    for (auto e : edges) {
      // daca conecteaza cc diferite, o adaugam la raspuns.
      // se testeaza de m ori
      if (!ds.Connected(e.a, e.b)) { 
        answer += e.c;
        // se apeleaza de maxim n - 1 ori
        ds.Link(e.a, e.b);
        mst_edges.push_back(e);
      }
    }
    return answer;
  }
};

int main() {
  ifstream cin("apm.in");
  ofstream cout("apm.out");

  int n, m; cin >> n >> m;
  Graph G(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a; --b;
    G.AddEdge(a, b, c);
  }
  cout << G.ComputeMST() << endl;
  cout << G.mst_edges.size() << endl;
  for (auto e : G.mst_edges) {
    cout << e.a + 1 << " " << e.b + 1 << '\n';
  }
  return 0;
}
