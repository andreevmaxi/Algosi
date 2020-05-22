#include <iostream>

int main(){
  int n;

  std::cin >> n;
  ++n;
  int dp[n][n];

  for(int i=0; i<n; ++i){
    dp[0][i]=0;
    dp[1][i]=1;
    dp[i][0]=0;
  }

  for(int i=1; i<n; ++i){
    int j=1;
    while(j<n && i!=1){
      dp[i][j] = dp[i][j-1] + (i==j) * 1 + (j<=i) * dp[i-j][j-1];
      ++j;
    }
  }

  std::cout << dp[n-1][n-1];
}
