#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

void insertAfter(dll * list, dln * node, dln * new){
  new -> prev = node;
  new -> next = node -> next;
  if (node -> next == NULL)
    list -> last = new;
  else
    node -> next -> prev = new;
  node -> next = new;
}

void insertBefore(dll * list, dln * node, dln * new){
  new -> next = node;
  new -> prev = node -> prev;
  if (node -> prev == NULL)
    list -> first = new;
  else
    node -> prev -> next = new;
  node -> prev = new;
}

void insertBeginning(dll * list, dln * new){
  if (list -> first == NULL){
    list -> first = new;
    list -> last = new;
    new -> prev = NULL;
    new -> next = NULL;
  }else{
    insertBefore(list, list -> first, new);
  }
}

void insertEnd(dll * list, dln * new){
  if (list -> last == NULL)
    insertBeginning(list, new);
  else
    insertAfter(list, list -> last, new);
}

void dllremove(dll * list, dln * node){
  if (node -> prev == NULL)
    list -> first = node -> next;
  else
    node -> prev -> next = node -> next;
  if (node -> next == NULL)
    list -> last = node -> prev;
  else
    node -> next -> prev = node -> prev;
  free(node);
}

void dllclear(dll * list){
  dln * node, * next;
  node = list -> first;
  while(node != NULL){
    next = node -> next;
    dllremove(list,node);
    node = next;
  }
}

void dllfree(dll * list){
  dllclear(list);
  free(list);
}

