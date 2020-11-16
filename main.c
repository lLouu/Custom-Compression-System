#include "headers/.main.h"

int main()
{
    option* run = (option*)malloc(sizeof(option));
    read_option_file(run, OPTION_PATH);
    char* tree_path = get_tree_path(run);
    char* compress_path = get_compress_path(run);

    if(run->mode)
    {
        encrypt(run->source, tree_path, compress_path);
    }
    else
    {
        decrypt(compress_path, tree_path, run->out);
    }
    

    free(tree_path);
    free(compress_path);
    free_option(run);
    return 0;
}