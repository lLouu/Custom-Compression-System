#include ".file.h"
#include "../headers/prototype/dictionary_proto.h"

int main()
{
    dico* d = compute_dico(SOURCE, DICO);

    free_dico(d);
    
    printf("\nend\n");
    return 0;
}