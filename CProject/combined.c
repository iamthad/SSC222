#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combined.h"

int main(int argc, char*argv[]){
  char * inputfilename;
  char * outputfilename;
  char defaultinputfilename[] = "input.fasta";
  char defaultoutputfilename[] = "output.fasta";
  dll sequences;
  sequences.first = NULL;
  sequences.last = NULL;

  inputfilename = &defaultinputfilename[0];
  outputfilename = &defaultoutputfilename[0];

  switch(argc){
    case 3:
      outputfilename = argv[2];
    case 2:
      inputfilename = argv[1];
    }
  printf("Reading sequences from file %s\n",inputfilename);
  fasta_read(inputfilename,&sequences);
  printf("Collapsing sequences. \n");
  printf("Sequences collapsed: \n");
  collapsesequences(&sequences);
  printf("Writing remaining sequences to file %s\n",outputfilename);
  fasta_write(outputfilename,&sequences,-1);

  dll_clear(&sequences);
  return 0;
}

void collapsesequences(dll * inputlist){
  dln * current, * compare, *next, *nextcompare;
  current = inputlist -> first;
  while(current != NULL){
    //printf("Comparing sequence %d\n",current->id);
    next = current->next;
    compare = inputlist -> first;
    while(compare != NULL){
      //printf("Comparing to %d\n",compare->id);
      nextcompare = compare->next;
      // Make sure we are not comparing to the same sequence.
      if((current->id != compare->id)&&(strstr(compare->data,current->data)!= NULL)){
        dln_remove(inputlist,current);

        print_sequence(stdout,current->sequence_length,current->header,current->data,80);
          
        
        break;
      }
      compare = nextcompare;
    }
    current = next;
  }
}

// Doubly-linked list handling functions based on examples on Wikipedia.
void dln_insert_after(dll * list, dln * node, dln * new){
  // Insert a node into a doubly-linked list after a specified node.
  new -> prev = node;
  new -> next = node -> next;
  // If the node is at the end of the list, update the list's last pointer
  if (node -> next == NULL)
    list -> last = new;
  else
    // Otherwise, update the previous pointer of the node that will now come after new
    node -> next -> prev = new;
  node -> next = new;
}

void dln_insert_before(dll * list, dln * node, dln * new){
  // Insert a node into a doubly-linked list before a specified node.
  new -> next = node;
  new -> prev = node -> prev;
  // If the node is at the beginning of the list, update the list's first pointer
  if (node -> prev == NULL)
    list -> first = new;
  else
    // Otherwise, update the next pointer of the node that will now come before new
    node -> prev -> next = new;
  node -> prev = new;
}

void dln_insert_beginning(dll * list, dln * new){
  // Insert a node into a doubly-linked list at the beginning
  // If the list is empty, the node is now the first and last elements of the list
  // And the node has no next or previous elements
  if (list -> first == NULL){
    list -> first = new;
    list -> last = new;
    new -> prev = NULL;
    new -> next = NULL;
  }else{
    dln_insert_before(list, list -> first, new);
  }
}

void dln_insert_end(dll * list, dln * new){
  // Insert a node into a doubly-linked list at the end
  // If the list is empty, inserting at the end is equivalent to inserting at the beginning
  if (list -> last == NULL)
    dln_insert_beginning(list, new);
  else
    dln_insert_after(list, list -> last, new);
}

void dln_remove(dll * list, dln * node){
  // Remove a node from a doubly-linked list
  // If the node was at the beginning of the list, the next node is now the first element
  if (node -> prev == NULL)
    list -> first = node -> next;
  else
    // Otherwise, the previous node's next node becomes the node's next node
    node -> prev -> next = node -> next;
  // Similarly, if the node was at the end, the previous node is now the last element
  if (node -> next == NULL)
    list -> last = node -> prev;
  else
    // Otherwise, the next node's previous node becomes the node's previous node
    node -> next -> prev = node -> prev;
  // Free the node. This is safe, since we have to always malloc these nodes due to the FLA
  free(node);
}

void dll_clear(dll * list){
  // Clear a doubly-linked list but do not free it since it may be statically declared
  dln * node, * next;
  // Step through the list and remove each node.
  node = list -> first;
  while(node != NULL){
    next = node -> next;
    dln_remove(list,node);
    node = next;
  }
}

int fasta_read(char * filename, dll * sequences){
  // Read a FASTA-formatted file into a doubly-linked list of sequences

  FILE *file;
  int n_sequences = 0; // Number of sequences read so far. Used as unique ID
  int c=0; // Temporary variable for each character
  int mode = 0; // Keeps track of the mode that the reader is operating in
  int location = 0; // Location in the file
  int sequence_length = 0; // Length of the current sequence
  int sequence_index = 0; // Location in the current sequence
  int header_index = 0; // Location in the header
  dln * sequence = NULL; // Pointer to the current sequence

  file = fopen(filename, "r");
  if(file == NULL){
    perror("Error with input file");
    exit(1);
  }

  // It is necessary to malloc() each sequence before we put it into the list because
  // of the flexible-length array at the end. So, we need to know how long each
  // sequence is before we read it. Thus, the reader operates in 4 modes:
  // SCANNING_HEADER, SCANNING_SEQUENCE, READING_HEADER, and READING_SEQUENCE.
  //
  // In SCANNING_HEADER mode, the reader waits for a newline to move to 
  // SCANNING_SEQUENCE. It is not necessary to determine the length of the header 
  // because we are assuming fixed-length headers. 
  //
  // In SCANNING_SEQUENCE mode, the reader counts non-newline characters to determine
  // the length of the sequence. When it hits the > again or EOF, it allocates memory
  // for the sequence and then jumps back to the beginning of the header and enters
  // READING_HEADER mode.
  //
  // In READING_HEADER mode, the reader takes each character of the header and
  // assigns it to the appropriate location in the header field. When it hits a 
  // newline, it moves to READING_SEQUENCE mode.
  //
  // In READING_SEQUENCE mode, the reader takes each non-newline, non-null character
  // in the sequence and assigns it to the appropriate location in the data field. 
  // When it hits the end of the sequence, it adds the sequence to the list of 
  // sequences, and if it has not hit EOF, saves the start location of the next
  // sequence, and switches to SCANNING_HEADER mode.
  
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
            // Finished scanning the sequence. Jump back to the start.
            fseek(file,location,SEEK_SET);
            // If there is a sequence, save it before we allocate the new one
            if (sequence != NULL)
              dln_insert_end(sequences,sequence);
            sequence = initialize_sequence(sequence_length,n_sequences);
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            break;
          case READING_SEQUENCE:
            // If we reach the end of a sequence
          default:
            // or are not started reading sequences yet, get ready.
            mode = SCANNING_HEADER;
            // Save the location so we can jump back here.
            location = ftell(file);
            // Iterate the sequence counter.
            n_sequences++;
            break;
        }
        break;

      case EOF:
        switch (mode){
          case SCANNING_SEQUENCE:
            // Finished scanning the sequence. Jump back to the start.
            fseek(file,location,SEEK_SET);
            // If there is a sequence, save it before we allocate the new one
            if (sequence != NULL)
              dln_insert_end(sequences,sequence);
            sequence = initialize_sequence(sequence_length,n_sequences);
            sequence_length = 0;
            mode = READING_HEADER;
            header_index = 0;
            break;
          case READING_SEQUENCE:
            // Save the last sequence
            dln_insert_end(sequences,sequence);
            break;
        }
          


      default:
        // Non-newline, non- ">", non-EOF characters
        switch (mode){
          case SCANNING_SEQUENCE:
            sequence_length++;
            break;
          case READING_HEADER:
            // Prevent overflows
            if (header_index > HEADER_LENGTH){
              fprintf(stderr,"Header would have overflowed.\n");
              exit(1);
            }
            // Make sure the sequence exists before we try to write to it
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
            // Prevent overflows
              fprintf(stderr,"Sequence would have overflowed.\n");
              exit(1);
            }
            // Make sure the sequence exists before we try to write to it
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
  }while(!feof(file)); //Use feof instead of checking if c == EOF so that fseek can reset it



  fclose(file);

  return 0;

}

int fasta_write(char * filename, dll * sequences, int column_length){
  // Write a FASTA file from a list of sequences
  FILE *file;
  dln * sequence;
  file = fopen(filename,"w");
  if(file == NULL){
    perror("Error with output file");
    exit(1);
  }
  if(sequences == NULL){
    fprintf(stderr,"Sequence list does not exist.\n");
    exit(1);
  }
  sequence = sequences -> first;
  while(sequence != NULL){
    // Iterate through the sequences and write them to the file.
    print_sequence(file,sequence->sequence_length,sequence->header,sequence->data,column_length);
    sequence = sequence->next;
  }
  fclose(file);
  return 0;

}

void print_sequence(FILE* file, int sequence_length, char * header, char * data, int column_length){
  // Print a sequence to a file pointer. This can be stdout to print to screen.
  char c;
  int i;
  int column = 0;
  // We can print the header all at once, since it should be a reasonable length
  fprintf(file,">%s\n",header);
  for(i=0;i<=sequence_length;i++){
    c = data[i];
    if(c != 0){
      fprintf(file,"%c",c);
      column++;
    }
    // For screen output or to write a proper FASTA file, we need to have a max column length
    // Setting column_length = -1 writes the whole thing out at once.
    if(column==column_length){
      fprintf(file,"\n");
      column = 0;
    }
  }
  fprintf(file,"\n");
}
  

dln * initialize_sequence(int sequence_length, int id){
  // Allocate and initialize a sequence.
  int i, length;
  dln * sequence;
  // Since dln has a flexible-length array for the data, need to make room for that.
  length = sizeof(dln)+(sequence_length+1)*sizeof(char);
  sequence = malloc(length);
  if(sequence != NULL){
    sequence -> sequence_length = sequence_length;
    sequence -> id = id;
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
