#include <bits/stdc++.h>

using namespace std;

struct DS {
  int n;
  vector<int> link, cnt;

  DS(int n) : n(n), cnt(n, 1), link(n, -1) {}
  
  int root(int a) {
    if (link[a] == -1) return a;
    int ret = root(link[a]);
    // rebalaning - shortening
    // "path compression"
    link[a] = ret;
    return ret;
  }
  
  bool Connected(int a, int b) {
    // BFS(a)
    return root(a) == root(b);
  }

  void Link(int a, int b) {
    a = root(a); b = root(b);
    if (cnt[a] > cnt[b]) 
      swap(a, b);
    
    // a devine fiu pt b
    link[a] = b; 
    cnt[b] += cnt[a];
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
