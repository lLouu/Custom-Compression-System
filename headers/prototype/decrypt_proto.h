#ifndef DE_PROTO
#define DE_PROTO

void decrypt(char* input_path, char* dico_path, char* output_path);

#else
#error "repeted call of decrypt_proto.h"
#endif