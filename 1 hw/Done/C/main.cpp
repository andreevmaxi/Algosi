#include <iostream>
#include <stack>
#include <algorithm>

int main(){
  int N;
  std::cin >> N;

  int Numbers[N];
  int LeftMax[N];
  int RightMax[N];
  std::stack<int> TmpS;

  TmpS.push(-1);
  for(int i=0; i<N; ++i){
    std::cin >> Numbers[i];
    while( TmpS.top() != -1 && Numbers[TmpS.top()]>=Numbers[i] ){
      TmpS.pop();
    }
    LeftMax[i] = TmpS.top();
    TmpS.push(i);
  }

  while(!TmpS.empty()){
   TmpS.pop();
  }
  TmpS.push(N);
  for(int i=N-1; i>=0; --i){
    while( TmpS.top() != N && Numbers[TmpS.top()]>=Numbers[i] ){
      TmpS.pop();
    }
    RightMax[i] = TmpS.top();
    TmpS.push(i);
  }

  long long Rectangles[N];
  for(int i=0; i<N; ++i){
    Rectangles[i] = (long long)Numbers[i]*(RightMax[i] - (LeftMax[i] + 1));
  }
  if(N>0){
    std::cout << *std::max_element(Rectangles, Rectangles + N);
  }else{
    std::cout << 0;
  }
  return 0;
}
