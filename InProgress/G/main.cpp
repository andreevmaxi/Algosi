#include <iostream>
#include <algorithm>

int main(){
  int n,m,l;
  std::cin >> n >> m >> l;

  int A[n][l];
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < l; ++j){
      std::cin >> A[i][j];
    }
  }
  int B[m][l];
  for(int i = 0; i < m; ++i){
    for(int j = 0; j < l; ++j){
      std::cin >> B[i][j];
    }
  }

  int q;
  std::cin >> q;
  for(int x=0; x<q; ++x){
    int i,j;
    std::cin >> i >> j;
    --i;
    --j;
    int k = 0;
    while(k < l && (B[j][k]>A[i][k])){
      ++k;
    }
    if(k>0 && std::max(A[i][k-1], B[j][k-1])<std::max(A[i][k],B[j][k])){
      --k;
    }
    std::cout << k+1 << std::endl;
  }
  return 0;
}
