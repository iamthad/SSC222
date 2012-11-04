#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void check_file_shape(FILE *file,char delimiter,int *lines, int *cols, int *max_fieldlength){
  int c = 0;
  int fieldlength = 0;
  int tabs;
  *lines = 0;
  *cols = 0;
  *max_fieldlength = 0;
  while (c != EOF){
    c = fgetc(file);
    if (c=='\n'){
      (*lines)++;
      if (fieldlength> *max_fieldlength)
        *max_fieldlength = fieldlength;
      fieldlength= 0;
      if ((tabs+1)>*cols)
        *cols = tabs+1;
      tabs = 0;
    }
    if (c==delimiter){
      tabs++;
      if (fieldlength > *max_fieldlength)
        *max_fieldlength = fieldlength;
      fieldlength= 0;
    }
    fieldlength++;

  }
}

int main(int argc, char *argv[]){
  FILE *file;
  int num_lines = 0;
  int num_cols = 0;
  int max_fieldlength = 0;
  int i,j,k,i_row,i_col,j_row,j_col,num_cities,matches;
  int c = 0;
  char delimiter = '\t';
  file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Invalid file name.\n");
    exit(1);
  }
  // Figure out how many lines there are in the file  
  check_file_shape(file,delimiter,&num_lines,&num_cols,&max_fieldlength);
  
  // There are at most num_cols*num_lines unique fields
  char raw_data [num_lines][num_cols][max_fieldlength];
  for (i=0;i<num_lines;i++){
    for (j=0;j<num_cols;j++){
      for (k=0;k<max_fieldlength;k++){
        raw_data[i][j][k] = 0;
      }
    }
  }


  // Read the city names, including spaces.
  rewind(file);
  i=0;
  j=0;
  k=0;
  c = fgetc(file);
  while(c != EOF){
    if (c=='\n'){
      i++;
      j=0;
      k=0;
    }
    else if(c==delimiter){
      j++;
      k=0;
    }
    else{
      raw_data[i][j][k]=c;
      k++;
    }
    c = fgetc(file);
  }
  
  // Count how many unique city names there are.
  num_cities=0;
  for(i=0;i<(num_lines*num_cols);i++){
    matches = 0;
    for(j=0;j<i;j++){
      i_row = i/(num_cols);
      i_col = i%(num_cols);
      j_row = j/(num_cols);
      j_col = j%(num_cols);
      printf("[%d,%d] %s : [%d,%d] %s\n",i_row,i_col,raw_data[i_row][i_col],j_row,j_col,raw_data[j_row][j_col]);
      // strcmp returns 0 if matching, non-0 if non-matching. This is non-intuitive.
      if(!strcmp(raw_data[i_row][i_col],raw_data[j_row][j_col])){
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
  printf("%d cities, %d unique.\n",num_lines*num_cols,num_cities);

  return 0;

}
