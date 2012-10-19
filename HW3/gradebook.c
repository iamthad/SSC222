/* Thadeus Fleming
 * Homework 3 Problem 3
 * SSC 222
 * Records 10 students' names and grades then prints them as well as identifying
 * highest and lowest grades. */

#include <stdio.h>
#define NAME_LENGTH 32
int main(){
  const int num_students = 10;
  int i, j, grade_temp, max_grade, max_grade_index, min_grade, min_grade_index, state;
  int char_temp;
  typedef struct student{
    int grade;
    char name[NAME_LENGTH];
  }student;
  student students[num_students];
  min_grade = 100;
  max_grade = -1;
  for (i=0; i < num_students; i++){
    for (j=0; j < NAME_LENGTH; j++){
        students[i].name[j] = 0; //Zero out each name to prevent junk characters.
        }
    printf("What is the name of student %d?\n",i+1);
    char_temp = 0;
    for (j=0; j < NAME_LENGTH; j++){
      char_temp = getchar();
      if (char_temp == ('\n') || char_temp == EOF){
        break;
      }else{
        students[i].name[j] = char_temp;
      }
    }
    state = 1;
    // Error handling loop
    while (state > 0){
      printf("What is their grade (between 0 and 100, integer)?\n");
      scanf("%d",&grade_temp);
      //scanf leaves the \n in stdin. This prevents more names from being read
      //So, we will manually grab that character off the buffer.
      getchar();
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
  }

}
