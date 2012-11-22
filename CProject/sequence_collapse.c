#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "fasta.h"
void collapsesequences(dll * inputlist, dll * outputlist);

int main(int argc, char*argv[]){
  char * inputfilename;
  char * outputfilename;
  char defaultinputfilename[] = "input.fasta";
  char defaultoutputfilename[] = "output.fasta";
  dll sequences;
  sequences.first = NULL;
  sequences.last = NULL;
  dll collapsed;
  collapsed.first = NULL;
  collapsed.last = NULL;

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
  collapsesequences(&sequences,&collapsed);
  printf("Writing sequences to file %s\n",outputfilename);
  fasta_write(outputfilename,&sequences,-1);
  printf("Sequences collapsed: \n");
  fasta_write("collapsed.fasta",&collapsed,-1);

  dllclear(&sequences);
  return 0;
}

void collapsesequences(dll * inputlist, dll * outputlist){
  dln * current, * compare, *next, *nextcompare, *temp;
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
        // One node cannot be in two lists. So, create a new node with the same data and put it in the output list.
        //printf("Match found. \n");
        temp = initialize_sequence(current->sequence_length,current->id);
        strncpy(temp->header,current->header,HEADER_LENGTH*sizeof(char));
        strncpy(temp->data,current->data,current->sequence_length*sizeof(char));
        insertEnd(outputlist,temp);
        dllremove(inputlist,current);
        break;
      }
      compare = nextcompare;
    }
    current = next;
  }
}




