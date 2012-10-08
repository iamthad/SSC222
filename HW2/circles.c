#include <stdio.h>
int main(){
  const double pi = 3.14159265358979323846;
  double r, c, A;
  int n, i;
  printf("Please input the number of concentric circles.\n");
  scanf("%d",&n);
  for(i=0; i<n; i++){
    r = 1 + 2*i;
    c = 2*pi*r;
    A = pi*r*r;
    printf("Circle #%d with radius %lf has circumference %lf and area %lf.\n",i+1,r,c,A);
  }
}
