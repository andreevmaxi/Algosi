#include <iostream>

struct Heap{
  std::vector<int> values;
  int End;

  Heap(){
    End = 0;
  }

  void SiftUp(int i){
    if(i != 0){
      while(i != 0 && values[(i - 1)/2] > values[i]){
        std::swap(values[(i - 1)/2], values[i]);
      }
    }
    return;
  }

  void SiftDown(int i){
      while(i < End && (values[i] > values[i * 2 + 1] || values[i] > values[i * 2 + 2])){
        std::swap(values[i], values[i * 2 + 1]);
        int f = values[i];
        int s = values[i * 2 + 2];
        values[i] = std::min(f, s);
        values[i * 2 + 2] = std::max(f, s);

        i = i * 2 + 2;
      }
  return;
  }

  void Insert(int i){
    values[End] = i;
    SiftDown(End);
    ++End;

    return;
  }

  int DeleteMin(){
    int Min = values[0];
    std::swap(values[End], values[0]);
    SiftDown(0);
    --End;

    return Min;
  }

  int PeakMin(){
    return values[0];
  }
};

int main()
{
  int n;


  int ans;

  Heap Heaps;
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
        Heaps.Insert(TmpElem);
        Ops.push(std::make_pair(1, TmpElem));
      } else if (State == "getMin")
      {
        while(Heapurya.values.size() > Heapurya.first && Heapurya.PeakMin() < TmpElem){
          Ops.push(std::make_pair(3, TmpElem));
          ++ans;
          Heaps.DeleteMin();
        }
        if(Heaps.values.size() <= Heapurya.End || Heapurya.PeakMin() != TmpElem){
          Heapurya.Insert(TmpElem);
          ++ans;
          Ops.push(std::make_pair(1, TmpElem));
        }

        Ops.push(std::make_pair(2, TmpElem));
      } else if (State == "removeMin")
      {
        if(Heapurya.values.size() <= Heapurya.first){
          Heapurya.Insert(0);
          ++ans;
          Ops.push(std::make_pair(1, 0));
        }
        Ops.push(std::make_pair(3, TmpElem));
        Heapurya.DeleteMin();
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
