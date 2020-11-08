#include "../headers/.main.h"
#include "file.h"

int main()
{
    int exit_code = 0;

    //reading
    FILE* target = fopen(TUTURU, "r");
    occurence*  occ = read_occ(target);
    fclose(target);

    //tree creation
    huffman* tree = occ_to_tree(occ);
    char buffer[1] = "\0";

    //dictionary creation
    FILE* d_file = fopen(DICO, "w");
    register_dico(tree, d_file, buffer);
    fclose(d_file);

    free_tree(tree);

    //dictionary reading
    d_file = fopen(DICO, "r");
    dico* d = read_dico(d_file);
    fclose(d_file);

    //encrypting
    FILE* tuturu = fopen(TUTURU, "r"), *out = fopen(COMPRESS, "w");
    encrypt(tuturu, out, d);
    fclose(tuturu);
    fclose(out);

    //tree recovering
    huffman* recover = create_tree();
    recover_tree(d, recover);

    //decrypting
    FILE* in = fopen(COMPRESS,"r");
    out = fopen(OUT, "w");
    decrypt(in, out, recover);

    free_dico(d);
    free_tree(recover);

    printf("%d\n", exit_code);
    return exit_code;
}