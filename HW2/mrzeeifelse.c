#include <stdio.h>

int main(){
  int temperature, month, coin;
  printf("It is time for Mr. Zee to partake in some leisure activity.\n");
  printf("What is the current temperature in °F?\n");
  fflush(stdout);
  scanf("%d",&temperature);
  if (temperature <= 80 && temperature >= 72){
    printf("Mr. Zee is going on a long walk.\n");
    printf("What is the number of the current month?\n");
    fflush(stdout);
    scanf("%d",&month);
    if(month > 7 && month < 11)
      printf("Mr. Zee will bring his umbrella.\n");
    else
      printf("Mr. Zee will not bring his umbrella.\n");
  }
  else{
    printf("Mr. Zee will stay home and read.\n");
    printf("Flip a coin. If heads, input 1. If tails, input anything else.\n");
    fflush(stdout);
    scanf("%d",&coin);
    if(coin == 1)
      printf("Mr. Zee will read science fiction.\n");
    else
      printf("Mr. Zee will read Greek mythology.\n");
}}
