/* Thadeus Fleming
 * Homework 3 Problem 3
 * SSC 222
 * Records 10 students' names and grades then prints them as well as identifying
 * highest and lowest grades. */

#include <stdio.h>

int main(){
  const int num_students = 10;
  int i, grade_temp, max_grade, max_grade_index, min_grade, min_grade_index, state;
  typedef struct student{
    int grade;
    char name[32];
  }student;
  student students[num_students];
  min_grade = 100;
  max_grade = -1;
  for (i=0; i < num_students; i++){
    printf("What is the name of student %d?\n",i+1);
    fflush(stdout);
    scanf("%s",&students[i].name[0]);
    state = 1;
    // Error handling loop
    while (state > 0){
      printf("What is their grade (between 0 and 100, integer)?\n");
      fflush(stdout);
      scanf("%d",&grade_temp);
      if (grade_temp <= 100 && grade_temp >= 0){
        state = 0;
        students[i].grade = grade_temp;
      } else {
        printf("Invalid grade.\n");
      }
    } 
    if (students[i].grade > max_grade){
      max_grade = students[i].grade;
      max_grade_index = i;
    }
    if (students[i].grade < min_grade){
      min_grade = students[i].grade;
      min_grade_index = i;
    }
  }
  for (i=0; i < num_students; i++){
    printf("%s: %d", students[i].name,students[i].grade);
    if (i == max_grade_index){
      printf(" MAXIMUM");
    }
    if (i == min_grade_index){
      printf(" MINIMUM");
    }
    printf("\n");
    fflush(stdout);
  }

}
