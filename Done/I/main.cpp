#include <iostream>
#include <utility>
#include <algorithm>

bool cmp(std::pair<int, int> a, std::pair<int, int> b);

int main(){
  int n,m;
  std::cin >> n;
  std::cin >> m;

  int Tmp1, Tmp2;
  std::pair<int, int> dots[2*n + m];
  for(int i=0; i<n; ++i){
    std::cin >> Tmp1 >> Tmp2;
    if(Tmp1 > Tmp2){
      std::swap(Tmp1, Tmp2);
    }
    dots[i*2].first = Tmp1;
    dots[i*2].second = 1 - (2*n+m);
    dots[i*2+1].first = Tmp2;
    dots[i*2+1].second = -1 + (2*n+m);
  }
  for(int i=2*n; i<2*n+m; ++i){
    std::cin >> Tmp1;
    dots[i].first = Tmp1;
    dots[i].second = i - 2*n;
  }
  sort(dots, dots+n*2+m);
  int Answer[m];

  Tmp2 = 0;
  for(int i=0; i<2*n+m; ++i){
    while(i<2*n+m && dots[i+1].first == dots[i].first){
      if(dots[i].second == 1 - (2*n+m)){
          ++Tmp2;
        }else if(dots[i].second == -1 + (2*n+m)){
          --Tmp2;
        }else{
        Answer[dots[i].second] = Tmp2;
        }
      ++i;
    }
    if(dots[i].second == 1 - (2*n+m)){
      ++Tmp2;
      }else if(dots[i].second == -1 + (2*n+m)){
      --Tmp2;
      }else{
      Answer[dots[i].second] = Tmp2;
      }
  }

  /*
  for(int i=0; i<2*n+m; ++i){
    std::cout << dots[i].first << " ";
  }
  std::cout << std::endl;
  for(int i=0; i<2*n+m; ++i){
    std::cout << dots[i].second << " ";
  }
  std::cout << std::endl;
  */
  for(int i=0; i<m; ++i){
    std::cout << Answer[i] << " ";
  }
  return 0;
}
