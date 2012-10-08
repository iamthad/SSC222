#include <stdio.h>

int main(){
  const double c = 299792458;
  double E,m;
  m = 20;
  E = m*c*c;
  printf("The relativistic energy  of a %lfkg object is %lfJ.\n",m,E);
  return 0;
}

