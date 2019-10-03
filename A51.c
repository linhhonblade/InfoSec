#include <stdio.h>
#include <stdlib.h>

// calculate one key stream bit
int get_key_stream_bit(int X[], int Y[], int Z[]){
  return X[18]^Y[21]^Z[22];
}

// shift array
int* shiftRightX(int* array){
  int addinX = array[13]^array[16]^array[17]^array[18];
  for (int i = 19; i >= 1; i--){
    array[i] = array[i-1];
  }
  array[0] = addinX;
  return array;
}

int* shiftRightY(int* array){
  int addinY = array[20]^array[21];
  for (int i = 21; i >= 1; i--){
    array[i] = array[i-1];
  }
  array[0] = addinY;
  return array;
}

int* shiftRightZ(int* array){
  int addinZ = array[7]^array[20]^array[21]^array[22];
  for (int i = 22; i >= 1; i--){
    array[i] = array[i-1];
  }
  array[0] = addinZ;
  return array;
}

// find major
int maj(int x, int y, int z){
  int sum = x + y + z;
  if( sum == 0 || sum == 1){
    return 0;
  }
  else{
    return 1;
  }
}

void A51(int X[], int Y[], int Z[], int n){
  printf("%d", get_key_stream_bit(X, Y, Z));
  for (int i = 1; i <= 9; i++){
    int major = maj(X[8], Y[10], Z[10]);
    if (X[8] == major){
      X = shiftRightX(X);
    }
    if (Y[10] == major){
      Y = shiftRightY(Y);
    }
    if (Z[10] == major){
      Z = shiftRightZ(Z);
    }
    printf("%d", get_key_stream_bit(X,Y,Z));
  }
  printf("\n");
}

int main(){
  int X[] = {1,1,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
  int Y[] = {1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1};
  int Z[] = {1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0};
  A51(X, Y, Z, 10);

}