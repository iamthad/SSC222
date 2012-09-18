#include <stdio.h>

int main(){
  const int N = 10;
  int sum;
  sum = N*(N+1)/2;
  printf("The sum of the first %d natural numbers is %d.\n",N,sum);
  return 0;
}

