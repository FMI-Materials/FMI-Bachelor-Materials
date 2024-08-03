#include <bits/stdc++.h>

using namespace std;
const int INF = 1e9;

struct DS {
  int n;
  vector<int> link, cnt, cost;

  DS(int n) : n(n), cnt(n, 1), link(n, -1), cost(n, INF) {}
  
  int root(int a) {
    while (link[a] != -1) a = link[a];
    return a;
  }
  
  bool Connected(int a, int b) {
    // BFS(a)
    return root(a) == root(b);
  }

  void Link(int a, int b, int c) {
    a = root(a); b = root(b);
    if (cnt[a] > cnt[b]) 
      swap(a, b);
    
    // a devine fiu pt b
    link[a] = b; 
    cost[a] = c;
    cnt[b] += cnt[a];
  }

  int Solve(int a, int b) {
    // maximul de pe lantul a-b
    int answer = 0;
    while (a != b) {
      if (cnt[a] > cnt[b]) swap(a, b);
      answer = max(answer, cost[a]);
      a = link[a];
    }
    return answer;
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
  DS ds;

  Graph(int n) : n(n), ds(n) {}

  void AddEdge(int a, int b, int c) {
    edges.emplace_back(a, b, c);
  }

  long long ComputeMST() {
    // 1. sortam muchiile.
    sort(edges.begin(), edges.end());
    // 2. pentru fiecare muchie in ordine,
    long long answer = 0;
    for (auto e : edges) {
      // daca conecteaza cc diferite, o adaugam la raspuns.
      // se testeaza de m ori
      if (!ds.Connected(e.a, e.b)) { 
        answer += e.c;
        // se apeleaza de maxim n - 1 ori
        ds.Link(e.a, e.b, e.c);
        mst_edges.push_back(e);
      }
    }
    return answer;
  }

  int Solve(int u, int v) {
    return ds.Solve(u, v);
  }
};

int main() {
  ifstream cin("radiatie.in");
  ofstream cout("radiatie.out");
  
  int n, m, q; cin >> n >> m >> q;
  Graph G(n);
  for (int i = 0; i < m; ++i) {
    int a, b, c; cin >> a >> b >> c; --a; --b;
    G.AddEdge(a, b, c);
  }

  cerr << G.ComputeMST() << endl;

  for (int i = 0; i < q; ++i) {
    int u, v; cin >> u >> v; --u; --v;
    cout << G.Solve(u, v) << '\n';
  }
  
  return 0;
}
