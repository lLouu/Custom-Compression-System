#ifndef E_PROTO
#define E_PROTO

/* Encrypt function
 *
 * @param input_path Copy parameter - the string of the path of the file to encrypt
 * @param dico_path Copy parameter - the string of the path of the dictionary file to create
 * @param output_path Copy parameter - the string of the path of the output to create
 * @return No return
 */
void encrypt(char* input_path, char* dico_path, char* output_path);
/* Encrypt function without compression 
 *
 * This function gives a readible file as result, if analysis is needed
 * 
 * @param input_path Copy parameter - the string of the path of the file to encrypt
 * @param dico_path Copy parameter - the string of the path of the dictionary file to create
 * @param output_path Copy parameter - the string of the path of the output to create
 * @return No return
 */
void encrypt_without_compression(char* input_path, char* dico_path, char* output_path);

#else
#error "repeted call of encrypt_proto.h"
#endif