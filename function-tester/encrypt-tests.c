#include ".file.h"
#include "../headers/common/header.h"
#include "../headers/common/struct.h"
#include "../headers/prototype/encrypt_proto.h"

int main()
{
    encrypt_without_compression(SOURCE, DICO, OUT);
    
    printf("\nend\n");
    return 0;
}