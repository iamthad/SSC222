#define SCANNING_HEADER 1
#define SCANNING_SEQUENCE 2
#define READING_HEADER 3
#define READING_SEQUENCE 4
#define HEADER_LENGTH 80

int fasta_read(char * filename, dll * sequences);
int fasta_write(char * filename, dll * sequences);
dln * initialize_sequence(int sequence_length);
