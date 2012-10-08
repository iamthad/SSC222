#include <stdio.h>

int main(){
  int temperature, month, coin;
  printf("It is time for Mr. Zee to partake in some leisure activity.\n");
  printf("What is the current temperature in °F?\n");
  fflush(stdout);
  scanf("%d",&temperature);
  switch(temperature){
  case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79:
  case 80:{
    printf("Mr. Zee is going on a long walk.\n");
    printf("What is the number of the current month?\n");
    fflush(stdout);
    scanf("%d",&month);
    switch(month){
      case 7: case 8: case 9: case 10: case 11:
        printf("Mr. Zee will bring his umbrella.\n");
        break;
      default:
        printf("Mr. Zee will not bring his umbrella.\n");
        break;}
    break;
  }
  default:{
    printf("Mr. Zee will stay home and read.\n");
    printf("Flip a coin. If heads, input 1. If tails, input anything else.\n");
    fflush(stdout);
    scanf("%d",&coin);
    switch(coin){
      case 1:
        printf("Mr. Zee will read science fiction.\n");
      default:
        printf("Mr. Zee will read Greek mythology.\n");}
}}}
