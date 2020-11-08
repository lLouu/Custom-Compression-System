#ifndef Q_PROTO
#define Q_PROTO

#include "../common/header.h"
#include "../common/struct.h"

void translate_to_bin(FILE* file_target, FILE* file_output);
int count(FILE* target);

occurence* new_occ();
void add_to_occ(char c, occurence** list_ptr);
occurence* read_occ(FILE* target);
void sort_occ(occurence** list);
void free_occ(occurence* list);

#endif