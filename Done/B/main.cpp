#include <cstdio>
#include <vector>
#include <stack>
#include <stdlib.h>

std::vector<char*> NumberVector;
std::stack<char*> AnswerStack;

void ProcessBuffer(char* NBuff, int SNum);

void AnswerProcessing();

bool LecsicCompare(char* a, char* b);

int main(){
  FILE* fp = fopen("number.in", "rb");
  fseek(fp, 0, SEEK_END);
  long SizeNumber = ftell(fp);
  rewind(fp);
  char* NumberBuffer = (char*) calloc(SizeNumber + 1, sizeof(char));
  *(NumberBuffer + SizeNumber) = '\0';
  fread(NumberBuffer, sizeof(char), SizeNumber, fp);
  fclose(fp);

  ProcessBuffer(NumberBuffer, SizeNumber);

  AnswerProcessing();
  fp = fopen("number.out", "w");
  while(!AnswerStack.empty()){
    fprintf(fp, "%s", AnswerStack.top());
    AnswerStack.pop();
  }
  fclose(fp);
  free(NumberBuffer);
  return 0;
}

void ProcessBuffer(char* NBuff, int SNum){
  char* TmpNum = NBuff;
  bool Last = 1;

  for(int i = 0; i < SNum; ++i){
    if(*(NBuff + i) < '0' || *(NBuff + i) > '9'){
      NumberVector.push_back(TmpNum);
      *(NBuff + i) = '\0';
      while(*(NBuff + i) < '0' || *(NBuff + i) > '9'){
        ++i;
      }
      Last = 0;
      if(i < SNum){
        Last = 1;
        TmpNum = NBuff + i;
      }
    }
  }

  if(Last){
    NumberVector.push_back(TmpNum);
  }

  return;
}

void AnswerProcessing(){
  std::stack<char*> TmpStack;

  for(int i = 0; i < NumberVector.size(); ++i){
    while(!AnswerStack.empty() && LecsicCompare(AnswerStack.top(), NumberVector[i])){
      TmpStack.push(AnswerStack.top());
      AnswerStack.pop();
    }
    AnswerStack.push(NumberVector[i]);
    while(!TmpStack.empty()){
      AnswerStack.push(TmpStack.top());
      TmpStack.pop();
    }
  }
  return;
}

bool LecsicCompare(char* a, char* b){
  int i = 0;
  int j = 0;
  bool Repeat1 = 0;
  bool Repeat2 = 0;

  while(*(a + i) == *(b + j) && !( *(a + i + 1) == '\0' && *(b + j + 1) == '\0') || (Repeat1 && Repeat2) ){
    if(*(a + i + 1) != '\0'){
      ++i;
      Repeat2 = 0;
    }else{
      Repeat2 = 1;
      i = 0;
    }
    if(*(b + j + 1) != '\0'){
      ++j;
      Repeat1 = 0;
    }else{
      Repeat1 = 1;
      j = 0;
    }
  }

  if( *(a + i) > *(b + j) ){
    return 1;
  }else{
    return 0;
  }
}
