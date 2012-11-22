// Flags for mode when reading. This helps make the code more meaningful.
#define SCANNING_HEADER 1
#define SCANNING_SEQUENCE 2
#define READING_HEADER 3
#define READING_SEQUENCE 4

// The FASTA format suggests that all lines be shorter than 80 characters.
#define HEADER_LENGTH 80

// The sequences are stored internally in doubly-linked lists
struct dln {
  struct dln * prev; // Pointer to previous item
  struct dln * next; // Pointer to next item
  int id; // A unique identifier
  char header[HEADER_LENGTH + 1]; // The header, plus an additional character for zero terminator
  int sequence_length; // Length of data
  char data[]; // The data, stored as a flexible-length array, since sequence lengths vary
};

// The doubly-linked list
struct dll {
  struct dln * first; // Pointer to first item
  struct dln * last; // Pointer to next item
};

// Define types for the above structures
typedef struct dln dln;
typedef struct dll dll;

void collapsesequences(dll * inputlist);
void dln_insert_after(dll * list, dln * node, dln * new);
void dln_insert_before(dll * list, dln * node, dln * new);
void dln_insert_beginning(dll * list, dln * new);
void dln_insert_end(dll * list, dln * node);
void dln_remove(dll * list, dln * node);
void dll_clear(dll * list);
int fasta_read(char * filename, dll * sequences);
int fasta_write(char * filename, dll * sequences, int column_length);
void print_sequence(FILE* file, int sequence_length, char * header, char * data, int column_length);
dln * initialize_sequence(int sequence_length, int id);
