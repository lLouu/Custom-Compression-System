#include "../headers/dictionary.h"

void add_to_occ(char c, occurence** list_ptr)
{
    if(*list_ptr == NULL)
    {
        *list_ptr = create_occ();
        (*list_ptr)->data = c;
        (*list_ptr)->occ = 1;
        (*list_ptr)->right = NULL;
        (*list_ptr)->left = NULL;
    }
    else
    {
        if((*list_ptr)->data == c)
        {
            (*list_ptr)->occ++;
        }
        else if ((*list_ptr)->data < c)
        {
            add_to_occ(c, &(*list_ptr)->left);
        }
        else
        {
            add_to_occ(c, &(*list_ptr)->right);
        }
    }
}
occurence* read_occ(char* target)
{
    FILE* target_file = fopen(target, "r");
    occurence* ret = NULL;

    char c = fgetc(target_file);
    while (c != EOF)
    {
        add_to_occ(c, &ret);
        c = fgetc(target_file);
    }
    
    fclose(target_file);
    return ret;
}

void occ_to_node(occurence* occ, node_list** buffer)
{
    if(occ != NULL)
    {
        node_list *ret = create_list();
        ret->node->data = occ->data;
        ret->node->size = occ->occ;

        node_list** scan = buffer;
        while(*scan != NULL && ret->node->size > (*scan)->node->size)
        {
            scan = &(*scan)->next;
        }
        node_list* temp = *scan;
        *scan = ret;
        ret->next = temp;
        
        occ_to_node(occ->right, buffer);
        occ_to_node(occ->left, buffer);
        free(occ);
    }
}
void compute_tree(node_list** l)
{
    if(*l != NULL && (*l)->next != NULL)
    {
        node_list* add = create_list();
        add->node->zero = (*l)->node;
        add->node->one = (*l)->next->node;
        add->node->size = add->node->zero->size + add->node->one->size;
        
        node_list* buffer = (*l)->next->next, **scan;
        free((*l)->next);
        free(*l);
        *l = buffer;
        scan = l;
        while (*scan != NULL && (*scan)->node->size < add->node->size)
        {
            scan = &(*scan)->next;
        }
        add->next = *scan;
        *scan = add;

        compute_tree(l);
    }
}
huffman* occ_to_tree(occurence* occ)
{
    if(occ == NULL)
    {
        return NULL;
    }
    node_list* l = NULL;
    occ_to_node(occ, &l);
    compute_tree(&l);
    huffman* ret = l->node;
    free(l);
    return ret;
}

void display(dico* d)
{
    if(d != NULL)
    {
        printf("%c : [", d->data);
        display(d->left);
        printf(",");
        display(d->right);
        printf("] ");
    }
}

char_SLL* copy(char_SLL* original)
{
    if(original == NULL)
    {
        return NULL;
    }
    char_SLL* scan = original->next, *ret = create_char(), *buffer = ret;
    ret->data = original->data;
    while(scan != NULL)
    {
        buffer->next = create_char();
        buffer = buffer->next;
        buffer->data = scan->data;
        scan = scan->next;
    }
    return ret;
}
dico* merge(dico* a, dico* b)
{
    if(a == NULL)
    {
        if(b == NULL)
        {
            return NULL;
        }
        return b;
    }
    if(b == NULL)
    {
        return a;
    }

    dico** scan = &a;
    while(*scan != NULL)
    {
        if(b != NULL && b->data < (*scan)->data)
        {
            dico* temp = b;
            b = b->left;
            temp->left = *scan;
            *scan = temp;
        }
        scan = &(*scan)->left;
    }
    if(b != NULL)
    {
        *scan = b;
    }
    return a;
}
dico* tree_to_dico(huffman* tree, char_SLL* buffer)
{
    if(tree != NULL)
    {
        if(tree->data != 0)
        {
            dico* ret = create_dico();
            ret->code = copy(buffer);
            ret->data = tree->data;
            return ret;
        }

        dico *zero, *one;
        if(buffer != NULL)
        {
            char_SLL* scan = buffer;
            while(scan->next != NULL)
            {
                scan = scan->next;
            }
            scan->next = create_char();
            scan->next->data = '0';
            zero = tree_to_dico(tree->zero, buffer);
            scan->next->data = '1';
            one = tree_to_dico(tree->one, buffer);
            free(scan->next);
            scan->next = NULL;
        }
        else
        {
            buffer = create_char();
            buffer->data = '0';
            zero = tree_to_dico(tree->zero, buffer);
            buffer->data = '1';
            one = tree_to_dico(tree->one, buffer);
            free(buffer);
        }

        dico* ret = merge(zero, one);
        return ret;
    }
    return NULL;
}
void register_dico(FILE* output_file, dico* d)
{
    if(d != NULL)
    {
        char_SLL* scan = d->code;
        while(scan != NULL)
        {
            fputc(scan->data, output_file);
            scan = scan->next;
        }
        fputc('-', output_file);
        fputc(d->data, output_file);

        register_dico(output_file, d->left);
        register_dico(output_file, d->right);
    }
    else
    {
        fputc('.', output_file);
    }
}


dico* compute_dico(char* input_path, char* output_path)
{
    occurence* occ = read_occ(input_path);
    huffman* tree = occ_to_tree(occ);
    char_SLL* buffer = NULL;
    dico* ret = tree_to_dico(tree, buffer);
    trees_balance_BST(&ret);
    free_tree(tree);

    FILE* output_file = fopen(output_path, "w");
    register_dico(output_file, ret);
    fclose(output_file);

    return ret;
}
