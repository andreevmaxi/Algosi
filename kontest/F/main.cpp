#include <iostream>
#include <vector>

std::vector<std::vector<int>> g;
std::vector<int> used;
std::vector<int> d;
std::vector<int> f;

int T=0;

void dfs(int v){
  used[v] = 1;
  d[v] = T++;

  for (int to : g[v]){
    if (!used[to]){
      dfs(to);
    }
  }

  f[v] = T++;

  return;
}

int main() {
  int n;
  std::cin >> n;

  g.resize(n+1);
  used.resize(n+1);
  d.resize(n+1);
  f.resize(n+1);

  int root;
  int a;
  for (int i=1; i<=n; ++i){
    std::cin >> a;
    if (!a){
      root = i;
    } else {
      g[a].push_back(i);
    }
  }

  dfs(root);
  int m;
  std::cin >> m;
  int b;
  for(int i=0; i<m; ++i){
    std::cin >> a >> b;
    std::cout << ((d[a] < d[b]) && (f[b] < f[a])) << std::endl;
  }
  return 0;
}
