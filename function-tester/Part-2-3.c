#include "../headers/.main.h"
#include "file.h"

int main()
{
    int exit_code = 0;

    FILE* target = fopen(OTHER, "r");
    occurence*  occ = read_occ(target);
    fclose(target);

    huffman* tree = occ_to_tree(occ);
    char buffer[1] = "\0";

    FILE* d = fopen(DICO, "w");
    create_dico(tree, d, buffer);
    fclose(d);

    free_tree(tree);

    printf("%d\n", exit_code);

    return exit_code;
}