#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm>

struct ListNode{
  std::vector<ListNode*> Nexts;
  std::vector<ListNode*> Prevs;
  int Color;
  long long Price;
  ListNode* OtherSide;
};

struct SkipList{
  ListNode* Begin;
  ListNode* End;
  int Size;

  SkipList(int n){
    Begin = new ListNode;
    End   = new ListNode;

    Begin->Nexts.resize(n);
    End->Nexts.resize(n);
    Begin->Prevs.resize(n);
    End->Prevs.resize(n);
    Size = n;

    for(int i=0; i<n; ++i){
      Begin->Nexts[i] = End;
      End->Nexts[i]   = 0; // означает, что мы дошли до конца нашего скип листа
      Begin->Prevs[i] = 0; // означает, что мы дошли до начала нашего скип листа
      End->Prevs[i]   = Begin;
    }

    Begin->Color = 0;
      End->Color = 4;
    Begin->Price = -1;
      End->Price = -1;

    return;
  }

  ListNode* Insert(int NewColor, long long NewPrice){
    ListNode* AfterInsert = SkipSearch(NewColor, NewPrice);  //AfterInsert->Nexts[i] != 0 нужно это учесть, что мы не можем вставлять после enda
    ListNode* NewShirt = new ListNode;

    NewShirt->Color = NewColor;
    NewShirt->Price = NewPrice;
    int SizeOfTower = 0;
    bool NewLevel = 1;
    while(SizeOfTower < Size && NewLevel){
      ++SizeOfTower;
      NewLevel = std::rand()%2;
    }

    NewShirt->Nexts.resize(SizeOfTower);
    NewShirt->Prevs.resize(SizeOfTower);

    for(int i = 0; i < SizeOfTower; ++i){
      while(AfterInsert->Nexts.size() < i + 1){
        AfterInsert = AfterInsert->Prevs[i-1]; // если наша найденная башенка слишком мала
      }

      NewShirt->Nexts[i] = AfterInsert->Nexts[i];
      NewShirt->Prevs[i] = AfterInsert;
      AfterInsert->Nexts[i] = NewShirt;
      NewShirt->Nexts[i]->Prevs[i] = NewShirt;
    }

    return NewShirt;
  }

  ListNode* Delete(ListNode* DeletingSide){
    ListNode* OS;

    OS = DeletingSide->OtherSide;

    for(int i = 0; i < DeletingSide->Nexts.size(); ++i){
      (DeletingSide->Prevs[i])->Nexts[i] = (DeletingSide->Nexts[i]);
      (DeletingSide->Nexts[i])->Prevs[i] = (DeletingSide->Prevs[i]);
    }

    delete DeletingSide;
    return OS;
  }

  ListNode* SkipSearch(int SearchingColor, long long SearchingPrice){
    ListNode* NowNode = Begin;
    int NowHeight = NowNode->Nexts.size() - 1;

    while((NowNode->Nexts[0]->Color < SearchingColor)
    || (NowNode->Nexts[0]->Color == SearchingColor && NowNode->Nexts[0]->Price < SearchingPrice)){
      // если следующая вершина на нижнем этаже имеет малый цвет или малую цену -> то мы должны дальше искать

      while((NowHeight > 0) && ( (NowNode->Nexts[NowHeight]->Color > SearchingColor)
      || (NowNode->Nexts[NowHeight]->Color == SearchingColor && NowNode->Nexts[NowHeight]->Price > SearchingPrice))){
        // если на нынешнем этаже или цвет неправильный или цена малая -> we need to go deeper
        --NowHeight;
      }
      NowNode = NowNode->Nexts[NowHeight];
    }

    return NowNode;
  }

  ~SkipList(){
    ListNode* DeletingNode = Begin;

    while(DeletingNode != End){
      DeletingNode = DeletingNode->Nexts[0];
      delete DeletingNode->Prevs[0];
    }

    delete DeletingNode;

    return;
  }
};

int main(){
  int n;

  std::cin >> n;

  struct UnsortedShirt{
    long long Price;
    int FaceSide;
    int SecSide;
  };

  UnsortedShirt Arr[n];

  for(int i = 0; i < n; ++i){
    std::cin >> Arr[i].Price;
  }
  for(int i = 0; i < n; ++i){
    std::cin >> Arr[i].FaceSide;
  }
  for(int i = 0; i < n; ++i){
    std::cin >> Arr[i].SecSide;
  }

  SkipList Faces(round((double)log(n+2) / (double)log(2)));
  SkipList Backs(round((double)log(n+2) / (double)log(2)));

  ListNode* NowShirtFace;
  ListNode* NowShirtBack;

  for(int i = 0; i < n; ++i){
    NowShirtFace = Faces.Insert(Arr[i].FaceSide, Arr[i].Price);
    NowShirtBack = Backs.Insert(Arr[i].SecSide,  Arr[i].Price);
    NowShirtFace->OtherSide = NowShirtBack;
    NowShirtBack->OtherSide = NowShirtFace;
  }

  NowShirtFace = Faces.Begin;
  NowShirtBack = Backs.Begin;

  int m;
  std::cin >> m;

  for(int i = 0; i < m; ++i){
    int CustomerColor;
    std::cin >> CustomerColor;

    NowShirtFace = (Faces.SkipSearch(CustomerColor - 1, 1000000001))->Nexts[0]; // тк максимальная цена 1 000 000 000
    NowShirtBack = (Backs.SkipSearch(CustomerColor - 1, 1000000001))->Nexts[0];

    if(NowShirtFace->Color != CustomerColor && NowShirtBack->Color != CustomerColor){
      std::cout << -1 << " ";
    } else if(NowShirtFace->Color != CustomerColor){
      std::cout << NowShirtBack->Price << " ";
      NowShirtFace = Backs.Delete(NowShirtBack);
      Faces.Delete(NowShirtFace);
    } else if(NowShirtBack->Color != CustomerColor){
      std::cout << NowShirtFace->Price << " ";
      NowShirtBack = Faces.Delete(NowShirtFace);
      Backs.Delete(NowShirtBack);
    } else if(NowShirtBack->Price > NowShirtFace->Price){
      std::cout << NowShirtFace->Price << " ";
      NowShirtBack = Faces.Delete(NowShirtFace);
      Backs.Delete(NowShirtBack);
    } else {
      std::cout << NowShirtBack->Price << " ";
      NowShirtFace = Backs.Delete(NowShirtBack);
      Faces.Delete(NowShirtFace);
    }
  }

  return 0;
}
