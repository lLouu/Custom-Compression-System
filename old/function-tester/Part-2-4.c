#include "../headers/.main.h"
#include "file.h"

int main()
{
    int exit_code = 0;
    FILE* target = fopen(TUTURU, "r");
    occurence*  occ = read_occ(target);
    fclose(target);

    huffman* tree = occ_to_tree(occ);
    char buffer[1] = "\0";

    FILE* d_file = fopen(DICO, "w");
    register_dico(tree, d_file, buffer);
    fclose(d_file);

    free_tree(tree);


    d_file = fopen(DICO, "r");
    dico* d = read_dico(d_file);
    fclose(d_file);

    FILE* tuturu = fopen(TUTURU, "r"), *out = fopen(COMPRESS, "w");
    encrypt(tuturu, out, d);
    fclose(tuturu);
    fclose(out);

    free_dico(d);

    printf("%d\n", exit_code);
    return exit_code;
}