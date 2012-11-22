#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "fasta.h"

int fasta_read(char * filename, dll * sequences){

  FILE *file;
  int num_sequences = 0;
  int c=0;
  int mode = 0;
  int location = 0;
  int sequence_length = 0;
  int sequence_index = 0;
  int header_index = 0;
  dln * sequence = NULL;

  file = fopen(filename, "r");
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
        }

        if (mode == READING_HEADER){
          mode = READING_SEQUENCE;
          sequence_index = 0;
        }
        break;

      case '>':
        switch (mode){
          case SCANNING_SEQUENCE:
            fseek(file,location,SEEK_SET);
            if (sequence != NULL){
              insertEnd(sequences,sequence);
            }
            sequence = initialize_sequence(sequence_length);
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            break;
          case READING_SEQUENCE:
          default:
            mode = SCANNING_HEADER;
            location = ftell(file);
            break;
        }
        num_sequences++;
        break;

      case EOF:
        switch (mode){
          case SCANNING_SEQUENCE:
            fseek(file,location,SEEK_SET);
            if (sequence != NULL)
              insertEnd(sequences,sequence);
            sequence = initialize_sequence(sequence_length);
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            break;
          case READING_SEQUENCE:
            insertEnd(sequences,sequence);
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
            if(sequence != NULL){
              sequence -> header[header_index] = c;
              header_index++;
            }else{
              fprintf(stderr,"Sequence does not exist.\n");
              exit(1);
            }
            break;
          case READING_SEQUENCE:
            if (sequence_index > sequence -> sequence_length){
              fprintf(stderr,"Sequence would have overflowed.\n");
              exit(1);
            }
            if(sequence != NULL){
              sequence -> data[sequence_index] = c;
              sequence_index++;
            }else{
              fprintf(stderr,"Sequence does not exist.\n");
              exit(1);
            }
            break;
        }
    }
  }while(!feof(file));



  fclose(file);

  return 0;

}

int fasta_write(char * filename, dll * sequences, int column_length){
  FILE *file;
  dln * sequence;
  file = fopen(filename,"w");
  int i, column = 0;
  char c;
  if(file == NULL){
    perror("Error with output file");
    exit(1);
  }
  if(sequences == NULL){
    fprintf(stderr,"Sequences is undefined for writing.\n");
    exit(1);
  }
  sequence = sequences -> first;
  while(sequence != NULL){
    // Print header
    fprintf(file,">");
    for(i=0;i<=HEADER_LENGTH; i++){
      c = sequence->header[i];
      if(c != 0)
        fprintf(file,"%c",c);
      else{
        break;
      }
    }
    fprintf(file,"\n");

    // Print sequence
    for(i=0;i<=sequence->sequence_length;i++){
      c = sequence->data[i];
      if(c != 0){
        fprintf(file,"%c",c);
        column++;
      }
      if(column==column_length){
        fprintf(file,"\n");
        column = 0;
      }
    }
    sequence = sequence->next;
    fprintf(file,"\n");
  }
  return 0;

}

dln * initialize_sequence(int sequence_length){
  int i, length;
  dln * sequence;
  length = sizeof(dln)+(sequence_length+1)*sizeof(char);
  sequence = malloc(length);
  if(sequence != NULL){
    sequence -> sequence_length = sequence_length;
    for(i = 0; i<=sequence_length; i++){
      sequence -> data[i] = 0;
    }
    for(i = 0; i<=HEADER_LENGTH; i++){
      sequence -> header[i] = 0;
    }
    return sequence;
  }else{
    fprintf(stderr,"Error allocating memory.\n");
    exit(1);
  }

}
