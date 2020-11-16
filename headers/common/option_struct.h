#ifndef O_STRUCT
#define O_STRUCT

/// list of the options
typedef struct option
{
    /// 0 for decompression ; 1 for compression
    char mode;
    /// The path to the source file for compression, or the the source folder for decompression
    char* source;
    /// The path to the output file for decompression, or the the source folder for compression
    char* out;
    /// The name of the compressed_file
    char* compress_file_name;
    /// The name of the tree_file
    char* tree_file_name;
}option;

#else
#error "repeted call of option_struct.h"
#endif