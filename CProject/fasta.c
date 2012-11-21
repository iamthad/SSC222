#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "fasta.h"

#define SCANNING_HEADER 1
#define SCANNING_SEQUENCE 2
#define READING_HEADER 3
#define READING_SEQUENCE 4
#define HEADER_LENGTH 80

int fasta_read(char * filename, dll * sequences){

  FILE *file;
  int num_sequences = 0;
  int c=0;
  int mode = 0;
  int location = 0;
  int sequence_length = 0;
  int sequence_index = 0;
  int header_index = 0;

  file = fopen(*filename, "r");
  if(file == NULL){
    perror("Error with input file");
    exit(1);
  }
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
            initialize_sequence(temp, sequence_length);
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

      case EOF:
        switch (mode){
          case SCANNING_SEQUENCE:
            fseek(file,location,SEEK_SET);
            if (temp != NULL)
              insertEnd(&sequences,temp);
            initialize_sequence(temp, sequence_length);
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            printf("Reading header.\n");
            break;
          case READING_SEQUENCE:
            insertEnd(&sequences,temp);
            break;
          default:
            fprintf(stderr,"Hit end of file unexpectedly.\n");
            exit(1);
        }
          


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



  fclose(file);

  return 0;

}

int initialize_sequence(dln * sequence, int sequence_length){
  sequence = malloc(sizeof(dln)+(sequence_length+1)*sizeof(char));
  if(sequence != NULL){
    sequence -> sequence_length = sequence_length;
    for(i = 0; i<=sequence_length; i++){
      sequence -> data[i] = 0;
    }
    for(i = 0; i<=HEADER_LENGTH; i++){
      sequence -> header[i] = 0;
    }
    return 0;
  }else{
    fprintf(stderr,"Error allocating memory.\n");
    exit(1);
  }

}
