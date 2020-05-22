#include <iostream>
#include <algorithm>
#include <string.h>

int DamerauLevenshteinDistance(std::string s1, std::string s2){
  int n = s1.length() + 1;
  int m = s2.length() + 1;
  int** tmp = new int* [n];

  for (int i=0; i<n; ++i){
    tmp[i] = new int[m];
    tmp[i][0] = i;
  }

  for (int j=0; j<m; ++j){
    tmp[0][j] = j;
  }

  for (int i = 1; i < n; ++i){
    for (int j = 1; j < m; ++j){
      int tmp2;
      if (s1[i-1] == s2[j-1]){
        tmp2 = 0;
      } else {
        tmp2 = 1;
      }
      tmp[i][j] = std::min(tmp[i-1][j]+1, std::min(tmp[i][j-1] + 1, tmp[i-1][j-1] + tmp2));

      if (i>1 && j>1 && s1[i-1] == s2[j-2] && s1[i-2] == s2[j-1]){
        tmp[i][j] = std::min(tmp[i][j], tmp[i-2][j-2] + tmp2);
      }
    }
  }

  return tmp[n - 1][m - 1];
}

int main(){
  std::string s1, s2;
  std::cin >> s1 >> s2;
  int ans = DamerauLevenshteinDistance(s1, s2);
  std::cout << ans;
}
