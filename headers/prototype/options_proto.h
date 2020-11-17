#ifndef O_PROTO
#define O_PROTO

#include "../common/option_struct.h"

void read_option_file(option* buffer, const char* option_path);
void free_option(option* o);

#else
#error "repeted call of option_proto.h"
#endif