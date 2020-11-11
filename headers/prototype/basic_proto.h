#ifndef B_PROTO
#define B_PROTO

#include "../common/header.h"
#include "../common/struct.h"

/* Create Function of occuence
 *
 * @return An empty occurence node
 */
occurence* create_occ();
/* Create Function of huffman
 *
 * @return An empty huffman tree node
 */
huffman* create_tree();
/* Create Function of node_list
 *
 * @return An empty list node
 */
node_list* create_list();
/* Create Function of char SLL
 *
 * @return An empty char node
 */
char_SLL* create_char();
/* Create Function of dictionary
 *
 * @return An empty dico node
 */
dico* create_dico();

/* Call function - Size of a char_SLL
 *
 * @param c Copy parameter - The start of the string to give lenght
 * @return The size of c
 */
int size(char_SLL* c);
/* Call function - Copy of a char_SLL
 *
 * @param original Copy parameter - The original SLL to copy 
 * @return The copy of original
 */
char_SLL* copy(char_SLL* original);

/* Free Function of occuence
 *
 * @param o Changed parameter - The occurence to free
 * @return No return
 */
void free_occ(occurence* o);
/* Free Function of huffman tree
 *
 * @param h Changed parameter - The huffman tree to free
 * @return No return
 */
void free_tree(huffman* h);
/* Free Function of a list
 *
 * @param n Changed parameter - The list to free
 * @return No return
 */
void free_list(node_list* n);
/* Free Function of a char SLL
 *
 * @param c Changed parameter - The char SLL to free
 * @return No return
 */
void free_char(char_SLL* c);
/* Free Function of a dictionary
 *
 * @param d Changed parameter - The dictionary to free
 * @return No return
 */
void free_dico(dico* d);

#else
#error "repeted call of basic_proto.h"
#endif