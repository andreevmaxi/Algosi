#include <iostream>
#include <algorithm>

const long long inf = (1 << 31) - 1;

int main()
{
  long long N, M, K, S, F;
  std::cin >> N >> M >> K >> S >> F;
  long long Map[M][3];
  for(int i=0; i<M; ++i){
    std::cin >> Map[i][0] >> Map[i][1] >> Map[i][2];
    --Map[i][0];
    --Map[i][1];
  }
  long long dp[N][K+1];
  for(int i=0; i<N; ++i){
    for(int j=0; j<=K; ++j){
      dp[i][j] = inf;
    }
  }
  dp[S-1][0] = 0;
  for(int i=1; i<=K; ++i){
    for(int j=0; j<M; ++j){
      if(dp[Map[j][1]][i] > (dp[Map[j][0]][i-1] + Map[j][2])){
        dp[Map[j][1]][i] = (dp[Map[j][0]][i-1] + Map[j][2]);
      }
    }
  }
  long long ans = inf;
  for(int i=0; i<=K; ++i){
    ans = std::min(ans, dp[F-1][i]);
  }
  if(ans == inf){
    std::cout << -1;
  } else {
    std::cout << ans;
  }
  return 0;
}
