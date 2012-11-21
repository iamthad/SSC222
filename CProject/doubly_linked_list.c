#include <stdio.h>
#include <stdlib.h>
#include "doubly_linked_list.h"

/*int main(){
  dll a;
  dln * x, * y, * z, * t;
  a.first = NULL;
  a.last = NULL;
  x = malloc(sizeof(dln));
  insertBeginning(&a,x);
  x -> val = 1;
  printf("x at: %p,val = %d, next = %p, prev = %p\n",x,x->val,x->next,x->prev);
  y = malloc(sizeof(dln));
  insertEnd(&a,y);
  y -> val = 3;
  z = malloc(sizeof(dln));
  printf("y at: %p,val = %d, next = %p, prev = %p\n",y,y->val,y->next,y->prev);
  insertBefore(&a,y,z);
  t = a.first;
  printf("z at: %p,val = %d, next = %p, prev = %p\n",z,z->val,z->next,z->prev);

  do{
    printf("At %p: %d\n",t,t->val);
    printf("Changing to %p\n",t->next);
    t = t->next;
  }while (t -> next != NULL);






  return 0;

}*/
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
