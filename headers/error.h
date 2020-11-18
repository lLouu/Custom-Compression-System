#ifndef ERROR
#define ERROR

#include "common/header.h"
#include <math.h>


#define ONE_ONE "basic.c"
#define ONE_TWO "error.c"
#define ONE_THREE "options.c"

#define TWO_ONE "dictionary.c"
#define TWO_TWO "tree.c"

#define THREE_ONE "encrypt.c"
#define THREE_TWO "decrypt.c"

#define FOUR_ONE "main.c"


#define UNKNOWN_FILE "File not registered"



#define SLL_LOOP_MESSAGE "SLL LOOP ERROR : A looping SLL has been detected"
#define FILE_NOT_FOUND_MESSAGE "FILE NOT FOUND : One of the file has not been open successfully"
#define CORRUPTION_MESSAGE "CORRUPTION ERROR : A sign of file corruption has been detected"
#define INVALID_INPUT_MESSAGE "INVALID INPUT : One of the input given is not the one expected"
#define INCOMPLETE_OPTION_MESSAGE "INCOMPLETE OPTION (Warning) : Your option file is incomplete. Default values are used"
#define TREE_CORUPTION_MESSAGE "TREE CORRUPTION (Warning) : The huffman tree is subject to allow file corruption. The compressed file could not be decompressable. Please take the secure version by modifying your options or by using a less-than-8-bits-compression to be sure no problem will happend"

#define UNKNOWN_ERROR "Error not defined"

#define FILE_WEIGHT 1
#define FILE_ID     2

#endif