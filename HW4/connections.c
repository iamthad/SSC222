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

int get_city_index(char city_array[], int num_cities, int name_length, char search_city[]){
  int i,j,index;
  char cities[num_cities][name_length];
  for(i=0;i<num_cities;i++){
    for(j=0;j<name_length;j++){
      cities[i][j] = city_array[j+name_length*i];
    }
  }
  index = -1; //Indicate errors

  for(i=0;i<num_cities;i++){
    if(!strcmp(search_city,cities[i])){
      index = i;
      break;
    }
  }
  return index;
}

void get_input(char input[], int input_length){
  int i, char_temp;
  for (i=0; i < input_length; i++)
    input[i]=0;
  for (i=0; i < input_length; i++){
    char_temp = getchar();
    if (char_temp == ('\n') || char_temp == EOF){
      break;
    }else{
      input[i] = char_temp;
    }
  }
}


int main(int argc, char *argv[]){
  FILE *file;
  int num_lines = 0;
  int num_cols = 0;
  int max_fieldlength = 0;
  int i,j,k,i_row,i_col,j_row,j_col,num_cities,matches,from_index,to_index;
  int from_city_set = 0;
  int to_city_set = 0;
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
    i_row = i/(num_cols);
    i_col = i%(num_cols);
    for(j=0;j<i;j++){
      j_row = j/(num_cols);
      j_col = j%(num_cols);
      // strcmp returns 0 if matching, non-0 if non-matching. This is non-intuitive.
      if(!strcmp(raw_data[i_row][i_col],raw_data[j_row][j_col])){
        matches = 1;
        break;
      }
    }
    if (matches==0){
      num_cities++;
    }
  }
  char cities[num_cities][max_fieldlength];

  // Fill cities with the unique city names. Indices become city ID numbers.

  k = 0;
  for(i=0;i<(num_lines*num_cols);i++){
    matches = 0;
    i_row = i/(num_cols);
    i_col = i%(num_cols);
    for(j=0;j<i;j++){
      j_row = j/(num_cols);
      j_col = j%(num_cols);
      if(!strcmp(raw_data[i_row][i_col],raw_data[j_row][j_col])){
        matches = 1;
        break;
      }
    }
    if (matches==0){
      strcpy(cities[k],raw_data[i_row][i_col]);
      k++;
    }
  }
  // Allocate connection matrix
  int connections[num_cities][num_cities];

  // -1 indicates cities are not connected
  for(i=0;i<num_cities;i++){
    for(j=0;j<num_cities;j++){
      connections[i][j] = 0;
    }
  }


  // 1 indicates cities are connected. This could be replaced with a distance value if minimum-distance route was desired.
  for(i=0;i<num_lines;i++){
    // Find the index of the city name in cities
    from_index = get_city_index(&cities[0][0],num_cities,max_fieldlength,raw_data[i][0]);
    to_index = get_city_index(&cities[0][0],num_cities,max_fieldlength,raw_data[i][1]);
    if(from_index == -1 || to_index == -1){
      fprintf(stderr,"Invalid city indices.\n");
      exit(1);
    }
    connections[from_index][to_index]=1;
    /* If connections are reciprocal:
     * connections[to_index][from_index]=1; */
    printf("%s connects to %s\n",cities[from_index],cities[to_index]);
  }

  char from_city[max_fieldlength],to_city[max_fieldlength];

  while(from_city_set==0){
    printf("Which city would you like to travel from? \n");
    get_input(from_city,max_fieldlength);
    from_index = get_city_index(&cities[0][0],num_cities,max_fieldlength,from_city);
    if(from_index == -1){
      fprintf(stderr,"City %s not found.\n",from_city);
    }else{
      from_city_set=1;
    }
  }
  printf("%s is city %d\n",from_city,from_index);

  while(to_city_set==0){
    printf("Which city would you like to travel to? \n");
    get_input(to_city,max_fieldlength);
    to_index = get_city_index(&cities[0][0],num_cities,max_fieldlength,to_city);
    if(to_index == -1){
      fprintf(stderr,"City %s not found.\n",to_city);
    }else{
      to_city_set=1;
    }
  }
  printf("%s is city %d\n",to_city,to_index);



  return 0;

}
