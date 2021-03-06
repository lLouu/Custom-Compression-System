#ifndef E_PROTO
#define E_PROTO

/* Encrypt function
 *
 * @param input_path Copy parameter - the string of the path of the file to encrypt
 * @param tree_path Copy parameter - the string of the path of the tree file to create
 * @param output_path Copy parameter - the string of the path of the output to create
 * @return No return
 */
void encrypt(const char* input_path, const char* output_path, int security);

#else
#error "repeted call of encrypt_proto.h"
#endif