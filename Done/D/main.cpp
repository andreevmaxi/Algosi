#include <iostream>
#include <list>

int main(){
  std::list<int> GoblinsFirst;
  std::list<int> GoblinsSecond;

  int N;
  char cmd;
  int NewGoblin;

  std::cin >> N;

  for(int i=0; i<N; ++i){
    std::cin >> cmd;
    switch(cmd){
      case('-'):{
      std::cout << GoblinsFirst.front() << std::endl;
      GoblinsFirst.pop_front();
        if(GoblinsSecond.size()>GoblinsFirst.size()){
          GoblinsFirst.push_back(GoblinsSecond.front());
          GoblinsSecond.pop_front();
        }
      }
      break;

      case('+'):{
        std::cin >> NewGoblin;
        GoblinsSecond.push_back(NewGoblin);
        if(GoblinsSecond.size()>GoblinsFirst.size()){
          GoblinsFirst.push_back(GoblinsSecond.front());
          GoblinsSecond.pop_front();
        }
      }
      break;

      case('*'):{
        std::cin >> NewGoblin;
        if(GoblinsSecond.size()>=GoblinsFirst.size()){
          GoblinsFirst.push_back(NewGoblin);
        }else{
          GoblinsSecond.push_front(NewGoblin);
        }
      }
      break;
    }
  }
  return 0;
}
