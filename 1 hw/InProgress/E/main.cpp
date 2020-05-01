#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>

unsigned int a, b;
unsigned int cur = 0;

unsigned int nextRand() {
  cur = cur * a + b;
  return cur >> 8;
}


int main(){
  int m,q;
  unsigned int Ans = 0;
  unsigned int NowPlus = 0;
  unsigned int NowLine = 0;
  std::cin >> m >> q;
  std::cin >> a >> b;
  std::vector<std::pair <long long, std::pair <int, long long>> > gym;
  for(int i=0; i<m; ++i){
    unsigned int add = nextRand();
    unsigned int l = nextRand();
    unsigned int r = nextRand();
    if(l > r) std::swap(l, r);
    gym.push_back(std::make_pair(l, std::make_pair(0, add)));
    gym.push_back(std::make_pair(r, std::make_pair(1, -add)));
  }
  for(int i=0; i<q; ++i){
    unsigned int l = nextRand();
    unsigned int r = nextRand();
    if(l > r) std::swap(l, r);
    gym.push_back(std::make_pair(l, std::make_pair(0, -10)));
    gym.push_back(std::make_pair(r, std::make_pair(0, -1)));
  }
  std::sort(gym.begin(), gym.end());

  for(int i = 0; i<gym.size(); ++i){
    switch((gym[i].second).first){
      case(0):{
        if((gym[i].second).second > 0){
          NowPlus += (gym[i].second).second;
        }else if((gym[i].second).second == -10){
          ++NowLine;
          if(i>0 && (gym[i-1].second).second == -10 && gym[i-1].first==gym[i].first){
            Ans += NowPlus;
          }else{
            for(int i=0; i<NowLine; ++i){
              Ans += NowPlus;
            }
          }
        }else{
          --NowLine;
        }
      }
      break;
      case(1):{
        NowPlus += (gym[i].second).second;
      }
      break;
    }
  }
  std::cout << Ans;
  return 0;
}
