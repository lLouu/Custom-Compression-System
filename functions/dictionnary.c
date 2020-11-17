#include "../headers/dictionary.h"

void add_to_occ(const char c, occurence** list_ptr)
{
    if(list_ptr == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 1);return;}

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
occurence* read_occ(const char* target)
{
    FILE* target_file = fopen(target, "r");
    if(target_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 1);return NULL;}
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
    if(buffer == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 2);return;}
    
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
    if(l == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 3);return;}
    
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
dico* tree_to_dico(const huffman* tree, char_SLL* buffer)
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

void check_all_one_node(huffman* tree)
{
    if(tree != NULL)
    {
        if(tree->data != 0)
        {
            error(TREE_CORUPTION, FILE_WEIGHT, FILE_ID, 1);
        }
        else
        {
            return check_all_one_node(tree->one);
        }
    }
}
void check_to_many_one(huffman* tree)
{
    if(tree != NULL)
    {
        int i = 1;
        while(i < 8 && tree->one != NULL)
        {
            i++;
            tree = tree->one;
        }
        if(tree->one != NULL)
        {
            error(TREE_CORUPTION, FILE_WEIGHT, FILE_ID, 2);
        }
        else
        {
            check_to_many_one(tree->zero);
        }
    }
}
void verify_corruption_tree(huffman* tree)
{
    check_all_one_node(tree);
    check_to_many_one(tree);
}


void register_tree(FILE* output_file, huffman* tree)
{
    if(output_file == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 5);return;}
    
    if(tree != NULL)
    {
        if(tree->data == 0)
        {
            fputc(':',output_file);
            register_tree(output_file, tree->zero);
            register_tree(output_file, tree->one);
        }
        else
        {
            if(tree->data == '.' || tree->data == ':' || tree->data == '#'){fputc('#', output_file);}
            fputc(tree->data, output_file);
            if(tree->zero != NULL || tree->one != NULL){error(CORRUPTION_ERROR,FILE_WEIGHT,FILE_ID,1);free_tree(tree->one);free_tree(tree->zero);}
        }
        free(tree);
    }
    else
    {
        error(CORRUPTION_ERROR,FILE_WEIGHT,FILE_ID,2);
        fputc('.', output_file);
    }
}
huffman* read_tree(FILE* tree_file)
{
    if(tree_file == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 2);return NULL;}
    char c = fgetc(tree_file);

    if(c == '.' || c == EOF){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 4);return NULL;}

    huffman* tree = create_tree();
    if(c == ':')
    {
        tree->zero = read_tree(tree_file);
        tree->one = read_tree(tree_file);
    }
    else
    {
        if(c == '#'){c = fgetc(tree_file);}
        tree->data = c;
    }
    return tree;
}

dico* compute_dico(const char* input_path, const char* output_path)
{
    occurence* occ = read_occ(input_path);
    huffman* tree = occ_to_tree(occ);
    if(CODE_BASE == 8){verify_corruption_tree(tree);}
    char_SLL* buffer = NULL;
    dico* ret = tree_to_dico(tree, buffer);
    balance_BST_all_left(&ret);

    FILE* output_file = fopen(output_path, "w");
    if(output_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 2);return NULL;}
    register_tree(output_file, tree);
    fclose(output_file);

    return ret;
}
