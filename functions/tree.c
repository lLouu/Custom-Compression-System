#include "../headers/tree.h"

int lenght(dico* d)
{
    if(d != NULL)
    {
        return 1 + lenght(d->left);
    }
    return 0;
}

dico* mid_of(dico* d)
{
    int len = lenght(d);

    dico* ret = d;
    for(int i = 0; i<len/2 - 1; i++)
    {
        ret = ret->left;
    }
    dico* buffer = ret;
    ret = ret->left;
    buffer->left = NULL;

    return ret;
}

void balance_BST_all_left(dico** tree)
{
    if(tree == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 1); return;}

    if(*tree != NULL && (*tree)->left != NULL)
    {
        dico* buffer = *tree;
        *tree = mid_of(buffer);
        (*tree)->right = buffer;
        balance_BST_all_left(&(*tree)->left);
        balance_BST_all_left(&(*tree)->right);
    }
}
