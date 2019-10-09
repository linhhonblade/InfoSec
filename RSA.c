#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

bool is_prime(int a){
  int upperbound = sqrt(a);
  for(int i = 2; i <= upperbound; i++){
    if(a % i == 0){
      return false;
    }
    continue;
  }
  return true;
}


int get_decryption_exp(int p, int q, int e){
  int phi = (p-1)*(q-1);
  for(int d = 1; d < phi; d ++){
    if((e*d) % phi == 1){
      return d;
    }
  }
}

int gcd(int a, int b){
  if (a==0||b==0){
    return 0;
  }
  if (a == b){
    return a;
  }
  if(a>b){
    return gcd(a-b, b);
  }
  return gcd(a, b-a);
}

int get_encryption_exp(int p, int q, int d){
  int phi = (p-1)*(q-1);
  for(int e = 1; e < phi; e++){
    if((e*d) % phi == 1){
      if(gcd(e, phi)==1){
        return e;
      }
    }
  }
}

int get_cipher_text(int p, int q, int e, int M){
  int phi = (p-1)*(q-1);
  int N = p*q;

}

void check_RSA1(int p, int q, int e, int M){
  printf("Public key is (%d, %d)\nPrivate key is %d\nPlain text is %d\nCipher text is %d\nDecryption of cipher text gets result %d\n", p*q, e, get_decryption_exp(p, q, e), M, calc_repeated_sqr(M, e, p*q), calc_repeated_sqr(calc_repeated_sqr(M, e, p*q), get_decryption_exp(p, q, e), p*q));
}

void check_RSA2(int p, int q, int d, int M){
  printf("Public key is (%d, %d)\nPrivate key is %d\nPlain text is %d\nCipher text is %d\nDecryption of cipher text gets result %d\n", p*q, get_encryption_exp(p, q, d), d, M, calc_repeated_sqr(M, get_encryption_exp(p,q,d), p*q), calc_repeated_sqr(calc_repeated_sqr(M, get_encryption_exp(p,q,d), p*q), d, p*q));
}

int main(){
  check_RSA1(5, 11, 3, 9);
  check_RSA2(3,11,7,5);
  if(is_prime(11)){
    printf("11 is prime\n");
  }
  return 0;
}