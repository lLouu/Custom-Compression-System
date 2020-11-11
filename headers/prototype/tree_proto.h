#ifndef T_PROTO
#define T_PROTO

#include "basic_proto.h"

/* Balance function of a tree
 * 
 * @param tree Changed parameter - The pointer to the tree to balance
 * @return No return
 */
void trees_balance_BST(dico** tree);

#else
#error "repeted call of tree_proto.h"
#endif