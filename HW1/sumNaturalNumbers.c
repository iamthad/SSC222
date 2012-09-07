#include <stdio.h>

int main(){
  const int N = 10;
  int sum;
  sum = N*(N+1)/2;
  printf("%d is the sum of the first %d natural numbers.\n",sum,N);
  return 0;
}

