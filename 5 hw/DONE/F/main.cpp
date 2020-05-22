#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  int dp[n];
  for(int i=0;i<n;++i){
    std::cin >> a[i];
  }
  std::sort(a.begin(), a.end());
  dp[1]=a[1]-a[0];
  dp[0]=dp[1];
  for(int i=2;i<n;++i){
    dp[i]=std::min(dp[i-2], dp[i-1]) + a[i] - a[i-1];
  }

  std::cout << dp[n-1];
  return 0;
}
