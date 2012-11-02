/* Thadeus Fleming
 * Homework 4 C Problem 2
 * SSC 222
 * Reads an arbitrary number of students' names and grades from a file then prints them as well as identifying  highest and lowest grades. */

#include <stdio.h>
#include <stdlib.h>
#define NAME_LENGTH 32
int main(int argc, char *argv[]){
  int num_students;
  int i, j, grade_temp, max_grade, max_grade_index, min_grade, min_grade_index, state;
  int char_temp;
  FILE *file;
  min_grade = 100;
  max_grade = -1;

  file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Invalid file name.\n");
    exit(1);
  }
  if (argc > 2){
    num_students = atoi(argv[2]);
  }else{
    printf("How many students?\n");
    scanf("%d",&num_students);
  }
  typedef struct student{
    int studentID;
    double grade;
    char name[NAME_LENGTH];
  }student;
  student students[num_students];
  
  for (i=0; i < num_students; i++){
    fscanf(file,"%d %lf", &students[i].studentID, &students[i].grade);
    for (j=0; j < NAME_LENGTH; j++){
        students[i].name[j] = 0; //Zero out each name to prevent junk characters.
        }
    char_temp = 0;
    for (j=0; j < NAME_LENGTH; j++){
      char_temp = getc(file);
      if (char_temp == ('\n') || char_temp == EOF){
        break;
      }else{
        students[i].name[j] = char_temp;
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
    // Prevent junk if there are fewer rows than num_students
    if(feof(file)){ 
      num_students = i;
    }
  }
  for (i=0; i < num_students; i++){
    printf("%d %s: %lf", students[i].studentID,students[i].name,students[i].grade);
    if (i == max_grade_index){
      printf(" MAXIMUM");
    }
    if (i == min_grade_index){
      printf(" MINIMUM");
    }
    printf("\n");
  }

}
