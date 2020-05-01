#include <iostream>
#include <vector>

using namespace std;

const int M = 20;

struct B_tree{
  struct Node_t{
    bool leaf;
    int n;
    vector <int> k;
    vector <Node_t*> pointers;
  };

  Node_t* root;

  B_tree(){
    root = new Node_t;
    root->leaf = true;
    root->n = 0;
    root->k.reserve(2 * M - 1);
    root->pointers.reserve(2 * M );

    return;
  }

  void split(Node_t* x, int p){
    Node_t* z = new Node_t;
    z->pointers.reserve(2 * M);
    z->k.reserve(2 * M - 1);
    Node_t* y = x->pointers[p];
    z->leaf = y->leaf;
    z->n = M - 1;

    for (int i = 0; i < M - 1; ++i){
      z->k[i] = y->k[i + M];
    }
    if (!(y->leaf)){
      for (int i = 0; i < M; ++i){
        z->pointers[i] = y->pointers[i + M];
      }
    }
    y->n = M - 1;

    for (int i = x->n; i > p; --i) {
      x->pointers[i + 1] = x->pointers[i];
    }
    x->pointers[p + 1] = z;

    for (int i = x->n - 1; i > p - 1; --i){
      x->k[i + 1] = x->k[i];
    }
    x->k[p] = y->k[M - 1];
    ++(x->n);
  }

  void add(int key){
    if (root->n == ((2 * M) - 1)){
      Node_t* New = new Node_t;
      New->leaf = false;
      New->n = 0;
      New->pointers.reserve(2 * M);
      New->k.reserve(2 * M - 1);
      New->pointers[0] = root;
      root = New;
      split(root, 0);
      ANC(root, key);
    }
    else {
      ANC(root, key);
    }

    return;
  }

  void ANC(Node_t* x, int key){ // add number in claster
    int i = x->n - 1;
    if (x->leaf){
      while (i >= 0 && key < x->k[i]){
        x->k[i + 1] = x->k[i];
        --i;
      }
      x->k[i + 1] = key;
      ++(x->n);
    }
    else{
      while (i >= 0 && key < x->k[i]){
        --i;
      }
      ++i;
      if (x->pointers[i]->n == ((2 * M) - 1)){
        split(x, i);
        if (key >= x->k[i]){
          ++i;
        }
      }
      ANC(x->pointers[i], key);
    }

    return;
  }

  pair <int, Node_t*> search(Node_t* x, int num){
    int now = 0;
    while (now < x->n && num > x->k[now]){
      ++now;
    }
    if (now < x->n && num == x->k[now]){
      return make_pair(now, x);
    } else if (x->leaf) {
      return make_pair(-1, nullptr);
    } else {
      return search(x->pointers[now], num);
    }
  }

  int next(Node_t* x, int num){
    int i = 0;
    while (i < x->n && num > x->k[i]){
      ++i;
    }
    if (i < x->n && num <= x->k[i] && !x->leaf){
      int ans = next(x->pointers[i], num);
      if (ans == -1) {
        return x->k[i];
      } else {
        return ans;
      }
    }
    if (x->leaf){
      if (i < x->n && num <= x->k[i]){
        return x->k[i];
      } else {
        return -1;
      }
    } else {
      return next(x->pointers[i], num);
    }
  }

  bool locate(int key){
    pair <int, Node_t*> answer = search(root, key);

    if (answer.first == -1){
      return false;
    } else {
      return true;
    }
  }
};


int main()
{
  B_tree A;

  int n;
  cin >> n;

  char cmd;
  int tmp1;

  int mod = -1;
  for (int i = 0; i < n; ++i){
    cin >> cmd >> tmp1;
    if (cmd == '+'){
      if (mod > 0){
        tmp1 = (tmp1 + mod) % 1000000000;
      }
      if(!A.locate(tmp1)){
        A.add(tmp1);
      }
    }
    if (cmd == '?'){
      mod = A.next(A.root, tmp1);
      cout << mod << '\n';
    } else {
      mod = -1;
    }
  }

  return 0;
}
