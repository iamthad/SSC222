#define HEADER_LENGTH 80
struct dln {
  struct dln * prev;
  struct dln * next;
  int sequence_length;
  char header[HEADER_LENGTH + 1];
  char data[];
};
struct dll {
  struct dln * first;
  struct dln * last;
};

typedef struct dln dln;
typedef struct dll dll;
void insertAfter(dll * list, dln * node, dln * new);
void insertBefore(dll * list, dln * node, dln * new);
void insertBeginning(dll * list, dln * new);
void insertEnd(dll * list, dln * node);
void dllremove(dll * list, dln * node);
