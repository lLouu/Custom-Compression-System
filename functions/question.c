#include "../headers/question.h"

//1.A
void translate_to_bin(FILE* file_target, FILE* file_output)
{
    char ch = 0;
    while((ch = fgetc(file_target)) != EOF && ch != '\n')
    {
        for (int i = 7; i >= 0; i--) {
            fprintf(file_output, ((ch >> i) & 1)?"1":"0");
        }
    }
}

//1.B
int count(FILE* target)
{
    int i = 0;
    char c = fgetc(target);

    while(c != EOF)
    {
        i++;
        c = fgetc(target);
    }

    return i;
}


//2.1.C
occurence* new_occ()
{
    occurence* occ = (occurence*)malloc(sizeof(occurence));
    occ->data = 0;
    occ->occ = 0;
    occ->next = NULL;

    return occ;
}
void add_to_occ(char c, occurence** list_ptr)
{
    if(*list_ptr == NULL)
    {
        *list_ptr = new_occ();
        (*list_ptr)->data = c;
        (*list_ptr)->occ = 1;
        (*list_ptr)->next = NULL;
    }
    else
    {
        if((*list_ptr)->data == c)
        {
            (*list_ptr)->occ++;
        }
        else
        {
            add_to_occ(c, &(*list_ptr)->next);
        }
    }
}
occurence* read_occ(FILE* target)
{
    occurence* ret = NULL;

    char c = fgetc(target);
    while (c != EOF)
    {
        add_to_occ(c, &ret);
        c = fgetc(target);
    }
    
    return ret;
}
void free_occ(occurence* list)
{
    if(list != NULL)
    {
        free_occ(list->next);
        free(list);
    }
}

//2.2.D
huffman* create_tree()
{
    huffman* ret = (huffman*)malloc(sizeof(huffman));

    ret->data = 0;
    ret->size = 0;
    ret->right = NULL;
    ret->left = NULL;

    return ret;
}
node_list* create_list()
{
    node_list* ret = (node_list*)malloc(sizeof(node_list));

    ret->node = create_tree();
    ret->next = NULL;

    return ret;
}


node_list* occ_to_node(occurence* occ)
{
    if(occ != NULL)
    {
        node_list *ret = create_list();
        ret->node = create_tree();
        ret->node->data = occ->data;
        ret->node->size = occ->occ;
        ret->next = occ_to_node(occ->next);

        free(occ);

        return ret;
    }
    return NULL;
}
void sort_node(node_list** list) 
{
    if(*list != NULL)
    {
        int cond = 1;
        node_list **s_buffer, *d_buffer;
        while(cond)
        {
            cond = 0;
            s_buffer = list;
            while((*s_buffer)->next != NULL)
            {
                if((*s_buffer)->node->size > (*s_buffer)->next->node->size)
                {
                    d_buffer = *s_buffer;
                    *s_buffer = (*s_buffer)->next;
                    d_buffer->next = (*s_buffer)->next;
                    (*s_buffer)->next = d_buffer;
                    cond = 1;
                }
                else
                {
                    s_buffer = &(*s_buffer)->next;
                }
                
            }
            
        }
    }
}
void compute_tree(node_list** l)
{
    if(*l != NULL && (*l)->next != NULL)
    {
        node_list* add = create_list();
        add->node->left = (*l)->node;
        add->node->right = (*l)->next->node;
        add->node->size = add->node->left->size + add->node->right->size;
        add->next = (*l)->next->next;
        sort_node(&add);

        free((*l)->next);
        free(*l);
        *l = add;
        compute_tree(l);
    }
}
huffman* occ_to_tree(occurence* occ)
{
    node_list* l = occ_to_node(occ);
    sort_node(&l);

    compute_tree(&l);
    huffman* ret = l->node;
    free(l);

    return ret;
}


void free_tree(huffman* tree)
{
    if(tree != NULL)
    {
        free_tree(tree->right);
        free_tree(tree->left);
        free(tree);
    }
}

void display(huffman* tree)
{
    if(tree != NULL)
    {
        if(tree->data != 0)
        {
            printf("%c : %d", tree->data, tree->size);
        }
        else
        {
            printf("[{");
            display(tree->left);
            printf("},{");
            display(tree->right);
            printf("}] : %d", tree->size);
        }
        
    }
}
