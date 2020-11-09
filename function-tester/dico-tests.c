#include ".file.h"
#include "../headers/.main.h"

int main()
{
    dico* d = compute_dico(SOURCE, OUT);

    printf("%c\n", d->data);

    free_dico(d);
    
    printf("\nend\n");
    return 0;
}