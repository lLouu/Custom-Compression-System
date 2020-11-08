#ifndef STRUCT
#define STRUCT

typedef struct occurence_list
{
    char data;
    int occ;
    struct occurence_list *next;
}occurence;

#else
#error "repeted call of struct.h"
#endif