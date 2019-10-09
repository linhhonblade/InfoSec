#include <stdio.h>
#include <stdlib.h>

struct Node {
  int coeff;
  struct Node* next;
};

struct Node* initNode(int coeff){
  struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
  temp->coeff = coeff;
  return temp;
}

struct Stack {
  int size;
  struct Node* top;
};

struct Stack stack = {0, NULL};

void Push(int coeff){
  struct Node* temp = initNode(coeff);
  temp->next = stack.top;
  stack.top = temp;
  stack.size++;
  return;
}

int Pop(){
  struct Node* temp = stack.top;
  stack.top = stack.top->next;
  int coeff = temp->coeff;
  free(temp);
  stack.size--;
  return coeff;
}

int calc_repeated_sqr(int x, int e, int m){
  if(e == 0){
    return 1;
  }
  else if(e == 1){
    return x % m;
  }
  int temp = e;
  while(temp != 1){
    Push(temp);
    temp /= 2;
  }
  int result;
  int current = x;
  while(stack.size != 0){
    temp = Pop();
    if (temp % 2 == 1){
      result = current*current*x % m;
      current = result;
    }
    if (temp % 2 == 0){
      result = current*current % m;
      current = result;
    }
  }
  return result;
}
int main(){
  printf("%d\n", calc_repeated_sqr(5, 1, 33));
  return 0;
}



