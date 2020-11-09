#ifndef STRUCT
#define STRUCT

typedef struct occurence_tree
{
    char data;
    int occ;
    struct occurence_tree *right;
    struct occurence_tree *left;
}occurence;

typedef struct Huffman_tree
{
    int size;
    char data;
    struct Huffman_tree* zero;
    struct Huffman_tree* one;
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
    struct dico* right;
    struct dico* left;
}dico;

#else
#error "repeted call of struct.h"
#endif