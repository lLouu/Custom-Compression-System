#ifndef STRUCT
#define STRUCT

/// Alphabetical Binary Search Tree of char occurences
typedef struct occurence_tree
{
    /// The char stocked
    char data;
    /// The number of occurence of data in the file
    int occ;
    /// The right member (occurence->right->data > occurence->data)
    struct occurence_tree *right;
    /// The left member (occurence->right->data < occurence->data)
    struct occurence_tree *left;
}occurence;

///Huffman tree node
typedef struct Huffman_tree
{
    /// The size of the tree
    int size;
    /// The char stocked, or 0 if it's not a dead end
    char data;
    /// The path which add a 0 to the code
    struct Huffman_tree* zero;
    /// The path which add a 1 to the code
    struct Huffman_tree* one;
}huffman;

/// A list of huffman trees sorted by size
typedef struct node_list
{
    /// The huffman tree stocked
    huffman* node;
    /// The next node
    struct node_list* next;
}node_list;

/// A string store as a Simple Linked List
typedef struct char_SLL
{
    /// The char stocked
    char data;
    /// The next char
    struct char_SLL* next;
}char_SLL;

typedef struct char_container
{
    char_SLL* content;
    int size;
}char_container;

/// An Aplphabetical AVL tree of a dictionary
typedef struct dico
{
    /// The char stocked
    char data;
    /// Its corresponding Huffman code
    char_container* code;
    /// The right member (dico->right->data > dico->data)
    struct dico* right;
    /// The left member (dico->right->data < dico->data)
    struct dico* left;
}dico;

#else
#error "repeted call of struct.h"
#endif