#include "headers/.main.h"

int main()
{
    option* run = (option*)malloc(sizeof(option));
    read_option_file(run, OPTION_PATH);

    if(run->mode)
    {
        encrypt(run->decompress, run->compress);
    }
    else
    {
        decrypt(run->compress, run->decompress);
    }
    
    free_option(run);
    return 0;
}