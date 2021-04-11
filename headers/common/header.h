#ifndef HEADER
#define HEADER

#include <stdio.h>
#include <stdlib.h>

/* CODE_BASE - 
 * The constant that define the byte compression ; 
 * Default value : 7 ; 
 * Optimized value : 8 ; 
 * By putting 8, some errors du to a EOF translation could appear
 * 
 * @see decrypt() - encrypt()
 */
#define CODE_BASE 8
#define EOF_to_EOF 5


#define SLL_LOOP_ERROR 1
#define FILE_NOT_FOUD 2
#define CORRUPTION_ERROR 3
#define INVALID_INPUT 4
#define INCOMPLETE_OPTION 5
#define TREE_CORUPTION 6

#else
#error "repeted call of header.h"
#endif