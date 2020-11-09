#include "../headers/basic.h"

occurence* create_occ()
{
    occurence* ret = (occurence*)malloc(sizeof(occurence));

    ret->data = 0;
    ret->occ = 0;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}
huffman* create_tree()
{
    huffman* ret = (huffman*)malloc(sizeof(huffman));

    ret->data = 0;
    ret->size = 0;
    ret->zero = NULL;
    ret->one = NULL;

    return ret;
}
node_list* create_list()
{
    node_list* ret = (node_list*)malloc(sizeof(node_list));

    ret->node = create_tree();
    ret->next = NULL;

    return ret;
}
char_SLL* create_char()
{
    char_SLL* ret = (char_SLL*)malloc(sizeof(char_SLL));

    ret->data = 0;
    ret->next = NULL;

    return ret;
}
dico* create_dico()
{
    dico* ret = (dico*)malloc(sizeof(dico));

    ret->data = 0;
    ret->code = NULL;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

void free_occ(occurence* o)
{
    if(o != NULL)
    {
        free_occ(o->left);
        free_occ(o->right);
        free(o);
    }
}
void free_tree(huffman* h)
{
    if(h != NULL)
    {
        free_tree(h->zero);
        free_tree(h->one);
        free(h);
    }
}
void free_list(node_list* n)
{
    if(n != NULL)
    {
        free_list(n->next);
        free_tree(n->node);
        free(n);
    }
}
void free_char(char_SLL* c)
{
    if(c != NULL)
    {
        free_char(c->next);
        free(c);
    }
}
void free_dico(dico* d)
{
    if(d != NULL)
    {
        free_dico(d->right);
        free_dico(d->left);
        free_char(d->code);
        free(d);
    }
}