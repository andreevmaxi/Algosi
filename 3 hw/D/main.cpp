#include <iostream>
#include <vector>

using namespace std;

const int M = 1000000;

struct B_tree{
  struct Node_t{
    int km;
    bool leaf;
    int n;
    vector <int> k;
    vector <Node_t*> pointers;

    int findKey(int num) {
      int idx=0;
      while (idx<n && k[idx] < num)
          ++idx;
      return idx;
      }

    void merge(int idx)
    {
      Node_t *child = pointers[idx];
      Node_t *sibling = pointers[idx+1];

      child->k[M-1] = k[idx];

      for (int i=0; i<sibling->n; ++i)
        child->k[i+M] = sibling->k[i];

      if (!child->leaf){
        for(int i=0; i<=sibling->n; ++i)
          child->pointers[i+M] = sibling->pointers[i];
      }

      for (int i=idx+1; i<n; ++i)
        k[i-1] = k[i];

      for (int i=idx+2; i<=n; ++i)
        pointers[i-1] = pointers[i];

      child->n += sibling->n+1;
      n--;

      delete(sibling);
      return;
    }

    void borrowFromPrev(int idx){
      Node_t *child=pointers[idx];
      Node_t *sibling=pointers[idx-1];

      for (int i=child->n-1; i>=0; --i)
        child->k[i+1] = child->k[i];

      if (!child->leaf){
        for(int i=child->n; i>=0; --i)
          child->pointers[i+1] = child->pointers[i];
      }

      child->k[0] = k[idx-1];

      if(!child->leaf)
          child->pointers[0] = sibling->pointers[sibling->n];

      k[idx-1] = sibling->k[sibling->n-1];

      child->n += 1;
      sibling->n -= 1;

      return;
    }

    void borrowFromNext(int idx){
      Node_t *child=pointers[idx];
      Node_t *sibling=pointers[idx+1];

      child->k[(child->n)] = k[idx];

      if (!(child->leaf))
          child->pointers[(child->n)+1] = sibling->pointers[0];

      k[idx] = sibling->k[0];

      for (int i=1; i<sibling->n; ++i)
          sibling->k[i-1] = sibling->k[i];

      if (!sibling->leaf){
        for(int i=1; i<=sibling->n; ++i)
          sibling->pointers[i-1] = sibling->pointers[i];
      }

      child->n += 1;
      sibling->n -= 1;

      return;
    }

    void fill(int idx){
      if (idx!=0 && pointers[idx-1]->n>=M){
        borrowFromPrev(idx);
      } else if (idx!=n && pointers[idx+1]->n>=M) {
        borrowFromNext(idx);
      } else {
        if (idx != n)
          merge(idx);
        else
          merge(idx-1);
      }
      return;
    }

    int getSucc(int idx){
      Node_t *cur = pointers[idx+1];
      while (!cur->leaf)
          cur = cur->pointers[0];

      return cur->k[0];
    }

    void removeFromLeaf (int idx){
      for (int i=idx+1; i<n; ++i)
          k[i-1] = k[i];
      n--;

      return;
    }

    int getPred(int idx) {
      Node_t *cur=pointers[idx];
      while (!cur->leaf)
          cur = cur->pointers[cur->n];

      return cur->k[cur->n-1];
    }

    void removeFromNonLeaf(int idx){
      int key = k[idx];

      if (pointers[idx]->n >= M)
      {
          int pred = getPred(idx);
          k[idx] = pred;
          pointers[idx]->remove(pred);
      } else if  (pointers[idx+1]->n >= M) {
          int succ = getSucc(idx);
          k[idx] = succ;
          pointers[idx+1]->remove(succ);
      } else {
          merge(idx);
          pointers[idx]->remove(key);
      }
      return;
    }

    void remove(int key) {
      int idx = findKey(key);
      --km;
      if (idx < n && k[idx] == key)
      {
        if (leaf){
          removeFromLeaf(idx);
        } else {
          removeFromNonLeaf(idx);
        }
      }
      else {
        bool flag = ( (idx==n)? true : false );

        if (pointers[idx]->n < M)
            fill(idx);
        if (flag && idx > n)
            pointers[idx-1]->remove(key);
        else
            pointers[idx]->remove(key);
      }
      return;
  }

  };

  Node_t* root;

  B_tree(){
    root = new Node_t;
    root->leaf = true;
    root->n = 0;
    root->k.reserve(2 * M - 1);
    root->pointers.reserve(2 * M );
    root->km = 0;

    return;
  }

  void split(Node_t* x, int p){
    Node_t* z = new Node_t;
    z->pointers.reserve(2 * M);
    z->k.reserve(2 * M - 1);
    Node_t* y = x->pointers[p];
    z->leaf = y->leaf;
    z->n = M - 1;
    z->km = M - 1;
    y->km -= M;

    for (int i = 0; i < M - 1; ++i){
      z->k[i] = y->k[i + M];
    }
    if (!(y->leaf)){
      for (int i = 0; i < M; ++i){
        z->pointers[i] = y->pointers[i + M];
        z->km += z->pointers[i]->km;
        y->km -= z->pointers[i]->km;
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
    ++(x->km);
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

  void remove(int key)
  {
    root->remove(key);

    if (root->n==0)
    {
      Node_t *tmp = root;
      if (root->leaf)
          root = NULL;
      else
          root = root->pointers[0];

        delete tmp;
    }
    return;
}

  int kmax(int i){
     i = root->km - i;
     Node_t* now = root;

     int NowI = 0;
     int NowEl = 0;
     while(!now->leaf && NowI < i){
       if(NowI + now->pointers[NowEl]->km < i){
         NowI += now->pointers[NowEl]->km;
         ++NowEl;
       } else {
         now = now->pointers[NowEl];
       }
     }

     return now->k[i - NowI];
  }

};

int main()
{
  B_tree A;

  int n;
  cin >> n;

  int cmd;
  int tmp;
  for(int i = 0; i < n; ++i){
    cin >> cmd >> tmp;
    switch(cmd){
      case(1):
        A.add(tmp);
        break;

      case(0):
        cout << A.kmax(tmp) << endl;
        break;

      case(-1):
        A.remove(tmp);
        break;
    }
  }

  return 0;
}
