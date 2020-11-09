#ifndef B_PROTO
#define B_PROTO

#include "../common/header.h"
#include "../common/struct.h"

occurence* create_occ();
huffman* create_tree();
node_list* create_list();
char_SLL* create_char();
dico* create_dico();

void free_occ(occurence* o);
void free_tree(huffman* h);
void free_list(node_list* n);
void free_char(char_SLL* c);
void free_dico(dico* d);

#endif