#include "../headers/.main.h"
#include "file.h"

int main()
{
    int exit_code = 0;

    FILE* target = fopen(TREE_TARG, "r");
    occurence*  occ = read_occ(target);
    fclose(target);

    huffman* tree = occ_to_tree(occ);
    
    display(tree);

    free_tree(tree);
    printf("\n%d\n", exit_code);
    return exit_code;
}