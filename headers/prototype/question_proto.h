#ifndef Q_PROTO
#define Q_PROTO

#include "../common/header.h"
#include "../common/struct.h"

void translate_to_bin(FILE* file_target, FILE* file_output);
int count(FILE* target);

occurence* new_occ();
void add_to_occ(char c, occurence** list_ptr);
occurence* read_occ(FILE* target);
void free_occ(occurence* list);

void sort_node(node_list** list);


huffman* create_tree();
node_list* create_list();


node_list* occ_to_node(occurence* occ);
void sort_node(node_list** list);
void compute_tree(node_list** l);
huffman* occ_to_tree(occurence* occ);


void free_tree(huffman* tree);
void display(huffman* tree);


void create_dico(huffman* tree, FILE* output_file, char* data);

#endif