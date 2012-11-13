#include <stdio.h>
#include <stdlib.h>
#define READING_HEADER 1
#define READING_SEQUENCE 2
int main(){
  FILE *file;
  int num_lines=0;
  int c=0;
  int num_sequences = 0;
  int header_length = 0;
  int max_header_length = 0;
  int sequence_length = 0;
  int max_sequence_length = 0;
  int total_sequence_length = 0;
  int total_header_length = 0;
  int mode = 0;
  file = fopen("input.fasta","r");
  do{
    c = fgetc(file);
    switch (c){
      case '\n':
        num_lines++;
        if (mode == READING_HEADER){
          mode = READING_SEQUENCE;
          sequence_length = 0;
          if (header_length > max_header_length)
            max_header_length = header_length;
        }
        break;
      case '>':
        num_sequences++;
        mode = READING_HEADER;
        header_length = 0;
        if (sequence_length > max_sequence_length)
          max_sequence_length = sequence_length;
        break;
      default:
        switch (mode){
          case READING_HEADER:
            header_length++;
            total_header_length++;
            break;
          case READING_SEQUENCE:
            sequence_length++;
            total_sequence_length++;
            break;
        }
    }
  }while(c!=EOF);
  printf("%d lines, %d sequences.\n",num_lines,num_sequences);
  printf("Maximum header length = %d. Maximum sequence length = %d.\n",max_header_length,max_sequence_length);
  printf("Total sequence length = %d B. Allocating the maximum for every sequence = %d B.\n",total_sequence_length*((int)sizeof(char)),num_sequences*max_sequence_length*((int)sizeof(char)));
  printf("This requires %lf x as much space.\n",((double)num_sequences*(double)max_sequence_length)/((double)total_sequence_length));
  printf("Total header length = %d B. Allocating the maximum for every header = %d B.\n",total_header_length*((int)sizeof(char)),num_sequences*max_header_length*((int)sizeof(char)));
  printf("This requires %lf x as much space.\n",((double)num_sequences*(double)max_header_length)/((double)total_header_length));


  return 0;
}
