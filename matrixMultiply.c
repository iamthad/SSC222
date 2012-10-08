#include <stdio.h>
int main(){
  int i, j, k;
  double myA[2][2], myB[2][2];
  double myC[2][2]={{0,0},{0,0}};
  // Read in matrices
  for(i=0;i<=1;i++){
    for(j=0;j<=1;j++){
      printf("Please enter the (%d,%d) element of matrix A.\n",i,j);
      scanf("%lf",&myA[i][j]);
      printf("You have entered %lf\n",myA[i][j]);
    }
  }

  for(i=0;i<=1;i++){
    for(j=0;j<=1;j++){
      printf("Please enter the (%d,%d) element of matrix B.\n",i,j);
      scanf("%lf",&myB[i][j]);
      printf("You have entered %lf\n",myB[i][j]);
    }
  }

  for(i=0;i<=1;i++){
    for(j=0;j<=1;j++){
      for(k=0;k<=1;k++){
        myC[i][j]=myC[i][j]+(myA[i][k]*myB[k][j]);
      }
      printf("%lf ",myC[i][j]);
    }
    printf("\n");}
}
  
