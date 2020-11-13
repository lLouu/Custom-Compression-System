#ifndef ERR_PROTO
#define ERR_PROTO

void error(const int code_error, const int file_weight, const int file_id, const int error_id);

#else
#error "repeted call of error_proto.h"
#endif