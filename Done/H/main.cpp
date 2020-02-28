#include <iostream>
#include <algorithm>
#include <vector>

int main(){
  int n,p,q;

  std::cin >> n >> p >> q;

  std::vector<long long> a;
  a.resize(n);
  for(int i=0; i<n; ++i){
    std::cin >> a[i];
  }
  long long Bashes = 0;
  int l,r;
  int m;
  std::sort(a.rbegin(), a.rend());
  l=a[0]/p;
  r=a[0]/q;
  if(a[0]%q > 0)
    ++r;
  while(l+1<r){
    m=(l+r)/2;
    Bashes = m;
    for(int NowMob = 0; NowMob < n; ++NowMob){
      if(((a[NowMob] - (long long)m * q) % (p - q)) > 0 && (a[NowMob] - (long long)m * q) > 0)
        --Bashes;
      Bashes -= std::max((long long)0, (a[NowMob] - (long long)m * q) / (p - q));
    }
    if(Bashes < 0){
      l = m;
    } else {
      r = m;
    }
  }
  std::cout << std::max(l,r);
  return 0;
}
