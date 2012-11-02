#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int count_lines(FILE *file){
  char c = 0;
  int num_lines = 0;
  while (c != EOF){
    c = fgetc(file);
    if (c=='\n')
      num_lines++;
  }
  return(num_lines);
}


int main(int argc, char *argv[]){
  FILE *file;
  int num_lines = 0;
  int i,j,num_cities,matches;
  char c = 0;
  file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Invalid file name.\n");
    exit(1);
  }
  // Figure out how many lines there are in the file  
  num_lines = count_lines(file);

  // There are at most 2*num_lines unique city names in the file
  char all_names [2*num_lines][32];
  for (i=0;i<2*num_lines;i++){
    for (j=0;j<=32;j++){
      all_names[i][j] = 0;
      }
  }

  // Read the city names, including spaces.
  rewind(file);
  i=0;
  j=0;
  c=0;
  while(c != EOF){
    c = fgetc(file);
    if (c=='\n' || c=='\t'){
      i++;
      j=0;
    }
    else{
      all_names[i][j]=c;
      j++;
    }
  }
  
  // Count how many unique city names there are.
  num_cities=0;
  for(i=1;i<2*num_lines;i++){
    matches = 0;
    for(j=0;j<i;j++){
      printf("%s : %s\n",all_names[i],all_names[j]);
      // strcmp returns 0 if matching, non-0 if non-matching. This is non-intuitive.
      if(!strcmp(all_names[i],all_names[j])){
        matches = 1;
        printf("Matches!\n");
        break;
      }
    }
    if (matches==0){
      num_cities++;
      printf("Unique!\n");
    }
  }
  printf("%d cities, %d unique.\n",2*num_lines,num_cities);

  return 0;

}
