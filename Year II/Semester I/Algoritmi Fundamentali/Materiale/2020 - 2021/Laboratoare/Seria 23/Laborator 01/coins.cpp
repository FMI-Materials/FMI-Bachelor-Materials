#include <bits/stdc++.h>

using namespace std;

struct Graph {
  int n;
  vector<int> coins;
  vector<vector<int>> graph, trans;
  vector<int> vis, comp;
  vector<long long> max_coins;
  vector<int> order, curr_comp;
  
  Graph(vector<int> coins) : 
    n(coins.size()), coins(coins), 
    graph(n), trans(n), vis(n, 0), comp(n), 
    max_coins(n, 0) {}

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
    curr_comp.push_back(node);
    for (auto nei : trans[node]) {
      if (!vis[nei]) {
        DFS2(nei, scc_id);
      }
    }
  }

  long long ComputeSCC() {
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
        // gasim componenta conexa noua 
        // in ordinea sortarii topologice
        curr_comp.clear();
        DFS2(i, scc_count);
        // ^ toata comp tare conexa e in curr_comp
        
        // calculez cate monezi am acumulat din "stanga"
        // maxim
        long long curr_max_coins = 0;
        for (auto node : curr_comp) {
          curr_max_coins = max(curr_max_coins, 
              max_coins[node]);
        }

        // adun numarul de monezi din mine
        for (auto node : curr_comp)
          curr_max_coins += coins[node];
        
        // propag raspunsul in nodurile viitoare
        for (auto node : curr_comp) {
          max_coins[node] = curr_max_coins;
          for (auto nei : graph[node]) {
            if (!vis[nei]) {
              max_coins[nei] = 
                max(max_coins[nei], curr_max_coins);
            }
          }
        }

        scc_count++;
      }
    }

    long long answer = 0;
    for (int i = 0; i < n; ++i)
      answer = max(answer, max_coins[i]);

    return answer;
  }
};


int main() {
  int n, m; cin >> n >> m;
  vector<int> coins(n);
  for (int i = 0; i < n; ++i)
    cin >> coins[i];
  Graph graph(coins);
  for (int i = 0; i < m; ++i) {
    // presupun 0 <= a, b < n
    int a, b; cin >> a >> b; 
    graph.AddEdge(a - 1, b - 1);
  }
  
  cout << graph.ComputeSCC() << endl;

  return 0;
}
