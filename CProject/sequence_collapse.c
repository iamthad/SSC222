#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "fasta.h"
#include "sequence_collapse.h"

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

  dllclear(&sequences);
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
        dllremove(inputlist,current);

        print_sequence(stdout,current->sequence_length,current->header,current->data,80);
          
        
        break;
      }
      compare = nextcompare;
    }
    current = next;
  }
}




