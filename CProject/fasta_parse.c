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
  int sequence_index = 0;
  int header_index = 0;
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
        if (mode == SCANNING_HEADER){
          mode = SCANNING_SEQUENCE;
          printf("Scanning sequence.\n");
        }

        if (mode == READING_HEADER){
          mode = READING_SEQUENCE;
          sequence_index = 0;
          printf("Reading sequence.\n");
        }
        break;

      case '>':
        switch (mode){
          case SCANNING_SEQUENCE:
            fseek(file,location,SEEK_SET);
            if (temp != NULL)
              insertEnd(&sequences,temp);
            temp = malloc(sizeof(dln)+sequence_length*sizeof(char));
            temp -> sequence_length = sequence_length;
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            printf("Reading header.\n");
            break;
          case READING_SEQUENCE:
          default:
            mode = SCANNING_HEADER;
            printf("Scanning header.\n");
            location = ftell(file);
            printf("Location: %d\n",location);
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
            if (header_index > HEADER_LENGTH){
              fprintf(stderr,"Header would have overflowed.\n");
              exit(1);
            }
            temp -> header[header_index] = c;
            header_index++;
            break;
          case READING_SEQUENCE:
            if (sequence_index > temp -> sequence_length){
              fprintf(stderr,"Sequence would have overflowed.\n");
              exit(1);
            }
            temp -> data[sequence_index] = c;
            sequence_index++;
            break;
        }
    }
  }while(c!=EOF);
  printf("%d\n",num_sequences);
  fclose(file);
  return 0;
}

