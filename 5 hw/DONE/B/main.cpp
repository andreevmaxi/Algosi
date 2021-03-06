#include <iostream>
#include <string>

int NnDB2(char* sr, int l, int r, int k, int n){
  int ans = 0;

  while(k>=0 && l >= 0 && r < n){
    if(sr[l] != sr[r]){
      --k;
    }
    if(k >= 0){
      ++ans;
    }
    --l;
    ++r;
  }
  return ans;
}

int DivB2(char* sr, int i, int k, int n){
  int l,r;
  l = i;
  r = i;

  return NnDB2(sr, l, r, k, n);
}

int main()
{
  int N, K;
  long long ans = 0;
  std::cin >> N >> K;
  char sr[N];

  for(int i=0; i<N; ++i){
    std::cin >> sr[i];
  }

  for(int i=0; i<N; ++i){
    ans += DivB2(sr, i, K, N);
  }
  for(int i=0; i<N-1; ++i){
    ans += NnDB2(sr, i, i+1, K, N);
  }
  std::cout << ans;
  return 0;
}
