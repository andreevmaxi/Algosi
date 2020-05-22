#include <iostream>
#include <deque>
#include <cmath>

const long long inf = (1 << 31) - 1;

int main()
{
  int n, m;
  int r, c;
  int x, y;

  std::cin >> n >> m;
  std::cin >> r >> c;
  std::cin >> x >> y;

  --r;
  --c;

  char map[n][m];

  std::pair<long long, long long> edges[n*m][4];
  long long path[n*m][2];
  bool visited[n*m];

  char tmp;
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      std::cin >> tmp;
      if(tmp == '*'){
        map[i][j] = 1;
      } else {
        map[i][j] = 0;
      }
      path[i*m + j][0] = inf;
      path[i*m + j][1] = inf;
      path[i*m + j][2] = inf;
      visited[i*m + j] = 0;
    }
  }

  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      if(j != 0){
        edges[i*m + j][0].first = i*m + j - 1;
        edges[i*m + j][0].second = map[i][j-1];
      } else {
        edges[i*m + j][0].first = -1;
        edges[i*m + j][0].second = -1;
      }

      if(i != 0){
        edges[i*m + j][1].first = (i-1)*m + j;
        edges[i*m + j][1].second = map[i-1][j];
      } else {
        edges[i*m + j][1].first = -1;
        edges[i*m + j][1].second = -1;
      }

      if(j != m-1){
        edges[i*m + j][2].first = i*m + j + 1;
        edges[i*m + j][2].second = map[i][j+1];
      } else {
        edges[i*m + j][2].first = -1;
        edges[i*m + j][2].second = -1;
      }

      if(i != n-1){
        edges[i*m + j][3].first = (i+1)*m + j;
        edges[i*m + j][3].second = map[i+1][j];
      } else {
        edges[i*m + j][3].first = -1;
        edges[i*m + j][3].second = -1;
      }
      std::cerr << edges[i*m + j][0].first << " " << edges[i*m + j][0].second<< std::endl
      << " " << edges[i*m + j][1].first << " " << edges[i*m + j][1].second<< std::endl
      << " " << edges[i*m + j][2].first << " " << edges[i*m + j][2].second<< std::endl
      << " " << edges[i*m + j][3].first << " " << edges[i*m + j][3].second << std::endl << std::endl;
    }
  }
  std::cerr << std::endl;
  std::deque<int> dots;
  dots.push_back(r*m + c);
  path[r*m + c][0] = 0;
  path[r*m + c][1] = 0;
  path[r*m + c][2] = 0;
  std::cerr << r*m + c << std::endl << std::endl;

  while (!dots.empty()){
    int v = dots.front();
    dots.pop_front();
    if(!visited[v]){
      for (int i=0; i<4; ++i){
        if(edges[v][i].first != -1){
          if ((path[v][0] + edges[v][i].second <= path[edges[v][i].first][0]) && ((!(v-edges[v][i].first) == 1) || (path[v][1] + 1 <= y))
          && ((!(v-edges[v][i].first) == -1) || (path[v][2] + 1 <= x))){
            if(((v-edges[v][i].first) == 1) && ((path[edges[v][i].first][0] != 0) || path[edges[v][i].first][1] > path[v][1] + 1)){
              path[edges[v][i].first][0] = path[v][0] + edges[v][i].second;
              path[edges[v][i].first][1] = path[v][1] + 1;
              path[edges[v][i].first][2] = path[v][2];
            } else if(((v-edges[v][i].first) == -1) || ((path[edges[v][i].first][0] != 0) || path[edges[v][i].first][2] > path[v][2] + 1)){
              path[edges[v][i].first][0] = path[v][0] + edges[v][i].second;
              path[edges[v][i].first][1] = path[v][1];
              path[edges[v][i].first][2] = path[v][2] + 1;
            } else if(std::abs(v-edges[v][i].first) != 1){
              path[edges[v][i].first][0] = path[v][0] + edges[v][i].second;
              path[edges[v][i].first][1] = path[v][1];
              path[edges[v][i].first][2] = path[v][2];
            }
            if (edges[v][i].second == 0){
              dots.push_front(edges[v][i].first);
            }
          }
        }
      }
      visited[v] = 1;
    }
  }

  long long ans = 0;
  for(int i=0; i<n; ++i){
    for(int j=0; j<m; ++j){
      std::cerr << path[i*m + j][0] << " ";
      if((path[i*m + j][0] == 0) && (path[i*m + j][1] <= y) && (path[i*m + j][2] <= x)){
        ++ans;
      }
    }
    std::cerr << std::endl;
  }
  std::cout << ans;
  return 0;
}
