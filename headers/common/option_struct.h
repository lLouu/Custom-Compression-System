#ifndef O_STRUCT
#define O_STRUCT

/// list of the options
typedef struct option
{
    /// 0 for decompression ; 1 for compression
    char mode;
    /// 1 if enable, 0 if not
    char security;
    /// The path to the file for compression
    char* compress;
    /// The path to the file for decompression
    char* decompress;
}option;

#else
#error "repeted call of option_struct.h"
#endif