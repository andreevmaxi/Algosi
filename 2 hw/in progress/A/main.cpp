#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <string>
#include <queue>
#include <cstdio>

struct QuickHeap{
  std::vector<int> values;
  int first;
  std::stack<int> pivots;

  QuickHeap(){
    first = 0;
    pivots.push(-1);
    return;
  }

  int QuickSelect(int left, int right, int PivotIndex){
    int PivotVal = values[PivotIndex];
    std::swap(values[PivotIndex], values[right]);
    int StoreIndex = left;

    for(int i = left; i < right; ++i){
      if(values[i] < values[PivotIndex]){
        std::swap(values[StoreIndex], values[i]);
        ++StoreIndex;
      }
    }
    std::swap(values[StoreIndex], values[right]);

    return StoreIndex;
  }

  int Particion(int right){
    while(pivots.top() != first){
      pivots.push(QuickSelect(first, right, rand() % (right - first) + first));
      right = pivots.top();
    }
  }

  int Insert(int NewE){
    std::stack<int> tmp;
    values.push_back(NewE);

    int NowPos = values.size();
    --NowPos;

    while(pivots.top() != -1){
      tmp.push(pivots.top());
      pivots.pop();
    }
    while(!tmp.empty() && NewE < values[tmp.top()]){
      std::swap(values[tmp.top() + 1], values[NowPos]);
      std::swap(values[tmp.top() + 1], values[tmp.top()]);
      NowPos = tmp.top();
      pivots.push(tmp.top() + 1);
      tmp.pop();
    }

    while(!tmp.empty()){
      pivots.push(tmp.top());
      tmp.pop();
    }

  return NowPos;
  }

  int DeleteMin(){
    int right = values.size();
    --right;

    while(pivots.top() != first && pivots.top() != first + 1){
      pivots.push(QuickSelect(first, std::max(first, right), std::min(std::max(first, right), rand() % std::max(1, (right - first)) + first)));
      right = pivots.top();
    }
    if(pivots.top() != first){
      pivots.push(first);
    }
    int DeletingElem = pivots.top();

    pivots.pop();
    ++first;

    return DeletingElem;
  }

  int PeakMin(){
    int right = values.size();
    --right;

    while(pivots.top() != first && pivots.top() != first + 1){
      pivots.push(QuickSelect(first, std::max(first, right), std::min(std::max(first, right), rand() % std::max(1, (right - first)) + first)));
      right = pivots.top();
    }

    if(pivots.top() != first){
      pivots.push(first);
    }
    return values[pivots.top()];
  }
};
int main()
{
  int n;
  int ans;

  QuickHeap Heapurya;
  std::queue<std::pair<int, int> > Ops;
  std::cin >> n;
  ans = n;
  std::vector<int> M5;

  for(int i = 0; i < n; ++i){
    std::string State;
    int TmpElem;

    std::cin >> State;
    if(State != "removeMin"){
      scanf("%d", &TmpElem);
    }

    if(State == "insert")
      {
        Heapurya.Insert(TmpElem);
        Ops.push(std::make_pair(1, TmpElem));
      } else if (State == "getMin")
      {
        while(Heapurya.values.size() > Heapurya.first && Heapurya.PeakMin() < TmpElem){
          Ops.push(std::make_pair(3, TmpElem));
          ++ans;
          Heapurya.DeleteMin();
        }
        if(Heapurya.values.size() <= Heapurya.first || Heapurya.PeakMin() != TmpElem){
          Heapurya.Insert(TmpElem);
          ++ans;
          Ops.push(std::make_pair(1, TmpElem));
        }

        Ops.push(std::make_pair(2, TmpElem));
      } else if (State == "removeMin")
      {
        if(Heapurya.values.size() <= Heapurya.first){
          ++ans;
          Ops.push(std::make_pair(1, 0));
        } else {
          Heapurya.DeleteMin();
        }
        Ops.push(std::make_pair(3, TmpElem));

      }
    }
  std::cout << ans;
  while(!Ops.empty()){
    switch(Ops.front().first){
      case(1):
        {
        std::cout << std::endl << "insert " << Ops.front().second;
        }
        break;

      case(2):
        {
        std::cout << std::endl << "getMin " << Ops.front().second;
        }
        break;

      case(3):
        {
        std::cout << std::endl << "removeMin";
        }
        break;
    }
    Ops.pop();
  }

  return 0;
}
