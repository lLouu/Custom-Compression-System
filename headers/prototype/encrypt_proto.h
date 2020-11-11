#ifndef E_PROTO
#define E_PROTO

void encrypt(char* input_path, char* dico_path, char* output_path);
void encrypt_without_compression(char* input_path, char* dico_path, char* output_path);

#else
#error "repeted call of encrypt_proto.h"
#endif