#ifndef DI_PROTO
#define DI_PROTO

#include "basic_proto.h"

/*Register function of a dictionary 
 *
 * Format : [code]-<char> ; 
 * preorder left tree display ; 
 * The dot are equivalent to NULL
 * 
 * @param output_file Changed parameter - A FILE* to the dictionary file open with the mode "w"
 * @param d Copy parameter - The dictionary to register
 * @return No return
 */
void register_dico(FILE* output_file, const dico* d);
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
/* Computation function of a dictionary
 * 
 * @param input_path Copied parameter - The path to the file to read to make the corresponding dictionary
 * @param output_path Copied parameter - The path were the tree registration file has to be created
 * @return The dictionary computed
 */
dico* compute_dico(const char* input_path, const char* output_path);

#else
#error "repeted call of dictionary_proto.h"
#endif