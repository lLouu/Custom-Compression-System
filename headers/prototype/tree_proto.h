#ifndef T_PROTO
#define T_PROTO

#include "basic_proto.h"

/* Balance function of a tree
 * 
 * @param tree Changed parameter - The pointer to the sorted list (all left tree) to balance as an AVL
 * @return No return
 */
void balance_BST_all_left(dico** tree);

#else
#error "repeted call of tree_proto.h"
#endif