#ifndef DE_PROTO
#define DE_PROTO

/* Decrypt function
 *
 * @param input_path Copy parameter - the string of the path of the file to decrypte
 * @param dico_path Copy parameter - the string of the path of the dictionary file to read
 * @param output_path Copy parameter - the string of the path of the output to create
 * @return No return
 */
void decrypt(char* input_path, char* dico_path, char* output_path);

#else
#error "repeted call of decrypt_proto.h"
#endif