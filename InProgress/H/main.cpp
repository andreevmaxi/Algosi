#include <iostream>

int main(){
  int n,p,q;

  std::cin >> n >> p >> q;

  int a[n];
  for(int i=0; i<n; ++i){
    std::cin >> a[i];
  }
  int NowHp[n];
  int NowMax=0;
  int l,r;

  for(int i=0; i<n; ++i){
    NowHp[i]=a[i];
  }
  std::sort(NowHp.rbegin(), NowHp.end());
  l=NowHp[0]/p + (NowHp[0]%p & 1);
  r=NowHp[0]/q + (NowHp[0]%q & 1);
  m=(l+r)/2;

  return 0;
}
