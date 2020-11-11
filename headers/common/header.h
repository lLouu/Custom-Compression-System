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
#define CODE_BASE 7

#else
#error "repeted call of header.h"
#endif