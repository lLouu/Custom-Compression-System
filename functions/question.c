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

// 2.3.E
void register_dico(huffman* tree, FILE* output_file, char* data)
{
    if(tree != NULL)
    {
        if(tree->data == 0)
        {
            int size = strlen(data);
            char* new_data = (char*)malloc((size+2)*sizeof(char));
            for(int i = 0; i < size; i++)
            {
                new_data[i] = data[i];
            }
            new_data[size+1] = '\0';
            new_data[size] = '0';
            register_dico(tree->right, output_file, new_data);
            new_data[size] = '1';
            register_dico(tree->left, output_file, new_data);
            free(new_data);
        }
        else
        {
            for(size_t i = 0; i<strlen(data); i++)
            {
                fputc(data[i], output_file);
            }
            fputc(tree->data, output_file);
        }
    }
}

//2.4.F
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

    ret->code = create_char();
    ret->data = 0;
    ret->next = NULL;

    return ret;
}

dico* read_dico(FILE* d)
{
    char c = fgetc(d);
    if(c != EOF)
    {
        dico* reed = create_dico();
        char_SLL *code = NULL, **buffer = (char_SLL**)malloc(sizeof(char_SLL*));

        while(c == '0' || c == '1')
        {
            *buffer = create_char();
            (*buffer)->data = c;
            if(code == NULL)
            {
                code = *buffer;
                buffer = &code->next;
            }
            else
            {
                buffer = &(*buffer)->next;
            }
            c = fgetc(d);
        }

        reed->code = code;
        reed->data = c;
        reed->next = read_dico(d);

        free(buffer);
        return reed;
    }
    return NULL;
}
void put(char c, FILE* out, dico* d)
{
    if(d != NULL)
    {
        if(d->data == c)
        {
            char_SLL* buffer = d->code;
            while(buffer != NULL)
            {
                fputc(buffer->data, out);
                buffer = buffer->next;
            }
        }
        else
        {
            put(c, out, d->next);
        }
    }
}
void encrypt(FILE* in, FILE* out, dico* d)
{
    char c = fgetc(in);
    if(c != EOF)
    {
        put(c, out, d);
        encrypt(in, out, d);
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
        free_dico(d->next);
        free_char(d->code);
        free(d);
    }
}
