#ifndef DI_PROTO
#define DI_PROTO

#include "basic_proto.h"

/*Register function of a huffman tree 
 *
 * Format : :[zero];[one] ; 
 * The dot are equivalent to NULL ; 
 * The presence of NULL is a sign of corrpution
 * 
 * @param output_file Changed parameter - A FILE* to the tree file open with the mode "w"
 * @param tree Copy parameter - The tree to register
 * @return No return
 */
void register_tree(FILE* output_file, const huffman* tree);
huffman* read_tree(FILE* tree_file);
/* Computation function of a dictionary
 * 
 * @param input_path Copied parameter - The path to the file to read to make the corresponding dictionary
 * @param output_path Copied parameter - The path were the tree registration file has to be created
 * @return The dictionary computed
 */
dico* compute_dico(const char* input_path, const char* output_path, int security);

#else
#error "repeted call of dictionary_proto.h"
#endif