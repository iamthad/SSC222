#include <stdio.h>
int main(){
double a,b,result;
char op;
printf("Basic calculator. Please enter two numbers.\n");
scanf("%lf",&a);
scanf("%lf",&b);
printf("Please enter one of the following operations: +, -, *, /\n");
scanf("%s",&op);
switch(op){
  case '+':
    result = a + b;
    break;
  case '-':
    result = a - b;
    break;
  case '*':
    result = a * b;
    break;
  case '/':
    result = a / b;
    break;
}
printf("%lf %c %lf = %lf\n",a,op,b,result);
}
