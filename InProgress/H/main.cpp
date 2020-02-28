#include <iostream>
#include <algorithm>
#include <vector>

int main(){
  int n,p,q;

  std::cin >> n >> p >> q;

  std::vector<int> a;
  a.resize(n);
  for(int i=0; i<n; ++i){
    std::cin >> a[i];
  }
  int Bashes = 0;
  int l,r;
  int m;
  std::sort(a.rbegin(), a.rend());
  l=a[0]/p;
  r=a[0]/q + (a[0]%q && 1);
  while(l+1<r){
    m=(l+r)/2;
    Bashes = m;
    for(int NowMob = 0; NowMob < n; ++NowMob){
      Bashes -= std::max(0, ((a[NowMob] - m * q) / (p - q) + (int)(((a[NowMob] - m * q) % (p - q)) && 1) ));
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
