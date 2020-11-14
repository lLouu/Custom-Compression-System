#ifndef DE_PROTO
#define DE_PROTO

/* Decrypt function
 *
 * @param input_path Copy parameter - the string of the path of the file to decrypte
 * @param tree_path Copy parameter - the string of the path of the tree file to read
 * @param output_path Copy parameter - the string of the path of the output to create
 * @return No return
 */
void decrypt(const char* input_path, const char* tree_path, const char* output_path);

#else
#error "repeted call of decrypt_proto.h"
#endif