#ifndef DI_PROTO
#define DI_PROTO

#include "basic_proto.h"

void register_dico(FILE* output_file, dico* d);
dico* compute_dico(char* input_path, char* output_path);

#else
#error "repeted call of dictionary_proto.h"
#endif