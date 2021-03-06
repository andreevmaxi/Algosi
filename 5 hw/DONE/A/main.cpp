#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
  int N, M;

  std::cin >> N >> M;
  int m[N + 1];
  int c[N + 1];
  for(int i=1; i<=N; ++i){
    std::cin >> m[i];
  }

  for(int i=1; i<=N; ++i){
    std::cin >> c[i];
  }

  int dp[N + 1][M + 1];

  int WMax = 0;
  for(int i=0; i<=N; ++i){
    dp[i][0] = 0;
  }
  for(int w=1; w<=M; ++w){
    dp[0][w] = 0;
    for(int i=1; i<=N; ++i){
      if(m[i] <= w && (dp[i-1][w] < (dp[i-1][w-m[i]] + c[i]))){
        dp[i][w] = (dp[i-1][w-m[i]] + c[i]);
      } else {
        dp[i][w] = dp[i-1][w];
      }
    }
    if(dp[N][WMax] < dp[N][w]){
      WMax = w;
    }
  }

  int i = N;
  int w = WMax;
  std::vector<int> ans;
  while(i != 0){
    if(dp[i-1][w] != dp[i][w]){
      w = w - m[i];
      ans.push_back(i);
      --i;
    } else {
      --i;
    }
  }
  std::cout << ans.size() << std::endl;
  for(int j=ans.size()-1; j>=0; --j){
    std::cout << ans[j] << " ";
  }
  return 0;
}
