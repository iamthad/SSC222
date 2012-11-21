#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

#define SCANNING_HEADER 1
#define SCANNING_SEQUENCE 2
#define READING_HEADER 3
#define READING_SEQUENCE 4
#define HEADER_LENGTH 80

int main(int argc, char*argv[]){
  FILE *file;
  int num_sequences = 0;
  int c=0;
  int mode = 0;
  int location = 0;
  int sequence_length = 0;
  char defaultname[] = "input.fasta";
  if (argc < 2)
    file = fopen(defaultname, "r");
  else
    file = fopen(argv[1],"r");

  dll sequences;
  dln * temp = NULL;



  do{
    c = fgetc(file);
    switch (c){
      case '\n':
        if (mode == SCANNING_HEADER)
          mode = SCANNING_SEQUENCE;
        if (mode == READING_HEADER)
          mode = READING_SEQUENCE;
        break;

      case '>':
        switch (mode){
          case SCANNING_SEQUENCE:
            fseek(file,location);
            if (temp ~= NULL)
              insertEnd(&sequences,temp);
            temp = malloc(sizeof(dln)+sequence_length*sizeof(char));
            temp -> sequence_length = sequence_length;
            sequence_length = 0;
            mode = READING_HEADER;
            break;
          case READING_SEQUENCE:
          default:
            mode = SCANNING_HEADER;
            break;
        }
        num_sequences++;
        break;

      default:
        switch (mode){
          case SCANNING_HEADER:
            break;
          case SCANNING_SEQUENCE:
            sequence_length++;
            break;
          case READING_HEADER:
            if header_index > HEADER_LENGTH{
              fprintf(stderr,"Header would have overflowed.\n");
              exit(1);
            }
            temp -> header[header_index] = c;
            header_index++;
            break;
          case READING_SEQUECE:
            if sequence_index > temp -> sequence_length{
              fprintf(stderr,"Sequence would have overflowed.\n");
              exit(1);
            }
            temp -> data[data_index] = c;
            data_index++;
            break;
        }
    }



  fclose(file);
  return 0;
  }while(c!=EOF);
}

