#include <iostream>
#include <map>

int main(){
  int n,m;

  std::cin >> n;
  std::map<int, int> First;
  for(int i=0; i<n; ++i){
    int tmp;
    std::cin >> tmp;
    First[tmp]++;
  }
  std::cin >> m;

  for(int i=0; i<m; ++i){
    int tmp;
    std::cin >> tmp;
    std::cout << First[tmp] << " ";
  }
  return 0;
}
