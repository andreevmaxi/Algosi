#include <iostream>
#include <fstream>
#include <algorithm>

long long Compare(int Numbers[], int l, int m, int r);

long long MergeSort(int Numbers[], int l, int r);

int main(){
  int N;
  std::ifstream in("inverse.in");
  in >> N;

  int a[N];
  long long Answer = 0;

  for(int i = 0; i<N; ++i){
    in >> a[i];
  }
  in.close();
  Answer += MergeSort(a, 0, N-1);


  std::ofstream out("inverse.out");
  out << Answer;
  out.close();
  return 0;
}

long long MergeSort(int Numbers[], int l, int r){
  long long Ans = 0;

  if(l<r){
    int m;

    m = l + (r-l)/2;
    Ans += MergeSort(Numbers, l, m);
    Ans += MergeSort(Numbers, m + 1, r);

    Ans += Compare(Numbers, l, m, r);
  }
  return Ans;
}

long long Compare(int Numbers[], int l, int m, int r){
  long long Ans = 0;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for(int i=0; i<n1; ++i){
    L[i] = Numbers[l + i];
  }
  for(int i=0; i<n2; ++i){
    R[i] = Numbers[m + 1 + i];
  }

  int i = 0;
  int j = 0;
  int k = l;

  while(i < n1 && j < n2){
    if(L[i] <= R[j]){
      Numbers[k] = L[i];
      ++i;
    }else{
      Numbers[k] = R[j];
      ++j;
      Ans += n1 - i;
    }
    ++k;
  }

  while(i < n1){
    Numbers[k] = L[i];
    ++i;
    ++k;
  }
  while(j < n2){
    Numbers[k] = R[j];
    ++j;
    ++k;
  }

  return Ans;
}
