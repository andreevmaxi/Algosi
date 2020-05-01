#include <iostream>

const int M = 3;

struct BNode_t{
  BNode_t dad;
  int data[M];
  BNode_t pointers[M + 1];
  int ns; // NodeSize
  bool leaf;

  BNode_t(){
    dad = 0;
    ns = 0;
    leaf = 0;
    for(int i = 0; i < M + 1; ++i){
      pointers[i] = 0;
    }
  }

  ~BNode_t(){
    dad = 0;
    for(int i = 0; i < M + 1; ++i){
      if(pointers[i] != 0){
        delete pointers[i];
        pointers[i] = 0;
      }
    }
    ns = M + 1;
  }
};

struct BTree_t{
  BNode_t* root;

  BTree_t();

  ~BTree_t();

  int newpos(BNode_t* now, int num);

  int add(int num);

  pair<BNode_t*, int> seek(int num);

  int next(int num);

  int del(int num);

  int split(int num);
};

BTree_t::BTree_t(){
  root = new BNode_t;
  root->leaf = 1;

  return;
}

BTree_t::~BTree_t(){
  delete root;

  return;
}

int BTree_t::ANC(BNode_t* now, int num){  // add number in claster
  int i = 0;
  while(i < now->ns && num < now->data[i]){
    ++i
  }
  for(int j = i; j < now->ns; ++j){ // check on capacity will be in other functions
    now->data[j + 1] = now->data[j];
    now->pointers[j + 1] = now->pointers[j];
  }
  now->pointers[now->ns] = now->pointers[now->ns - 1];
  now->data[i] = num;                   // and pointers needs to be ->
  now->pointers[i + 1] = 0;
  ++(now->ns);
  return i; // returning a position of new number
}

int BTree_t::add(int num){
  int i = 0;
  BNode_t* now = root;
  while(i < now->ns && num < now->data[i]){
    if(num > now->data[i]){
      ++i;
    } else if(now->pointers[i] != 0) {
      now = now->pointers[i];
      i = 0;
    }
    if(i == now->ns && now->pointers[i] != 0){
      now = now->pointers[i];
    }
  }
  if(now->ns == M){
    split(now);
    //dalshe drodolzhenie poiska
  }
  ++(now->ns);

  for(int j = now->ns; j > i; --j){
    now->data[j] = now->data[j - 1];
  }
  now->data[i] = num;

  return 0;
}

int BTree_t::split(BNode_t* now){
  if(now == root){
    BNode_t* dad = new BNode_t*;
    dad->pointers[0] = now;
    now->dad = dad;
    root = dad;
  }
  if(now->dad->ns == M){
    split(now->dad);
  }
  int i = ANC(now->dad, now->data[M/2]);

  BNode_t* SecondLeaf = new BNode_t*;
  SecondLeaf->dad = now->dad;
  for(int j = M/2; j < M + 1; ++j){
    SecondLeaf->pointers[j - M/2] = now->pointers[j];
    now->pointers[j] = 0;
  }
  now->data[M/2] = 0;
  for(int j = M/2 + 1; j < M; ++j){
    SecondLeaf->data[j - M/2] = now->data[j];
    now->data[j] = 0;
  }
  now->dad->pointers
}

pair<BNode_t*, int> BTree_t::seek(BNode_t* now, int num){
  int i = 0;
  while (i < now->ns && num > now->data[i]){
    ++i;
  }
  if(i < now->ns && num == now->data[i]){
    return std::make_pair(BNode_t* now, int i);
  }
  if(now->leaf){
    return std::make_pair(BNode_t* 0, int M + 1);
  } else {
    return BTree_t::seek(now->pointers[i], num);
  }
}

int main()
{
  return 0;
}
