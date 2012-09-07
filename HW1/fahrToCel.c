#include <stdio.h>

int main() {
  float F;
  float C;
  F = 100;
  C = (F-32)*5/9;
  printf("%.1f° F =  %.1f° C\n",F,C);
  return 0;
}
