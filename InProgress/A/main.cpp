#include <iostream>
#include <fstream>
#include <algorithm>

int main(){
  int N;
  std::ifstream in("inverse.in");
  in >> N;

  std::pair<int, int> a[N];
  long long Answer = 0;

  for(int i = 0; i<N; ++i){
    in >> a[i].first;
    a[i].second = i;
  }
  in.close();
  std::sort(a, a+N);

  for(int i = 0; i<N; ++i){
    Answer += std::max(0, (a[i].second - i));
  }

  std::ofstream out("inverse.out");
  out << Answer;
  out.close();
  return 0;
}
