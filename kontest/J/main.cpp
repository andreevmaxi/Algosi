#include <fstream>
#include <iostream>
#include <algorithm>
#include <deque>
#include <stdio.h>
#include <vector>

const long long inf = (1 << 31) - 1;

int main()
{
  std::ifstream ifst("kefir.in");
  std::ofstream ofst("kefir.out");
  long long N, M;

  ifst >> N >> M;

  std::vector <std::vector<std::pair<int, int>>> path(N);
  long long d[N+1];
  long long was[N+1];
  for(long long i=0; i<N; ++i){
    path[i].reserve(50);
    d[i] = inf;
    was[i] = 0;
  }
  d[0]=0;
  long long tmp1, tmp2, tmp3;
  for(long long i=0; i<M; ++i){
    ifst >> tmp1 >> tmp2 >> tmp3;
    path[tmp1-1].push_back(std::make_pair(tmp2-1, tmp3));
    path[tmp2-1].push_back(std::make_pair(tmp1-1, tmp3));
  }

  long long temp = 0;
  long long minindex;
  bool found;
  found = 1;
  while(found){
    found = 0;
    long long mini = 300000;
    for (long long i=0; i<N; ++i){
      if ((was[i] == 0) && (!found || (d[i]<mini))){
        mini = d[i];
        minindex = i;
        found = 1;
      }
    }
    if (found){
      for (long long i=0; i<path[minindex].size(); ++i){
        temp = mini + path[minindex][i].second;
        if (temp < d[path[minindex][i].first]){
          d[path[minindex][i].first] = temp;
        }
      }
      was[minindex] = 1;
    }
  }

  if(d[N-1] == inf){
    ofst << -1;
  } else {
    ofst << d[N-1];
  }
  return 0;
}
