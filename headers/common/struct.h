#ifndef STRUCT
#define STRUCT

typedef struct occurence_list
{
    char data;
    int occ;
    struct occurence_list *next;
}occurence;

typedef struct Huffman_tree
{
    int size;
    char data;
    struct Huffman_tree* left;
    struct Huffman_tree* right;
}huffman;

typedef struct node_list
{
    huffman* node;
    struct node_list* next;
}node_list;

typedef struct char_SLL
{
    char data;
    struct char_SLL* next;
}char_SLL;

typedef struct dico
{
    char data;
    char_SLL* code;
    struct dico* next;
}dico;

#else
#error "repeted call of struct.h"
#endif