#include <iostream>

const int M = 2;

struct BNode_t{
  BNode_t dad;
  int data[2 * M - 1];
  BNode_t pointers[2 * M];
  int ns; // NodeSize
  bool leaf;

  BNode_t(){
    dad = 0;
    ns = 0;
    leaf = 0;
    for(int i = 0; i < 2 * M; ++i){
      pointers[i] = 0;
    }
  }

  ~BNode_t(){
    dad = 0;
    for(int i = 0; i < 2 * M - 1; ++i){
      if(pointers[i] != 0){
        delete pointers[i];
        pointers[i] = 0;
      }
    }
    ns = 2 * M - 1;
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

int BTree_t::split(BNode_t* y){
  BNode_t* z = new BNode_t*;
  BNode_t* x = y->dad;

  z->leaf = y->leaf;

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
