#include "../headers/decrypt.h"

char_SLL* getcode(char* input_path)
{
    FILE* input_file = fopen(input_path, "r");
    int surplus = CODE_BASE - fgetc(input_file);
    if(surplus == CODE_BASE)
    {
        surplus = 0;
    }
    char_SLL** ret = (char_SLL**)malloc(sizeof(char_SLL*)), **scan = ret;
    *ret = NULL;
    char c = fgetc(input_file);

    while(c != EOF)
    {
        for(int i = CODE_BASE - 1; i>=0; i--)
        {
            *scan = create_char();
            (*scan)->data = ((c >> i) & 1)?'1':'0';
            scan = &(*scan)->next;
        }
        c = fgetc(input_file);
    }
    
    scan = ret;
    int s = size(*ret);
    for(int i = 0; i<s-surplus; i++)
    {
        scan = &(*scan)->next;
    }
    free_char(*scan);
    *scan = NULL;

    char_SLL* buffer = *ret;
    free(ret);
    fclose(input_file);
    return buffer;
}

dico* read_dico(FILE* dico_file)
{
    
    char c = fgetc(dico_file);
    if(c != EOF)
    {
        char_SLL *code = NULL, **buffer = (char_SLL**)malloc(sizeof(char_SLL*));

        while(c != '-' && c != '.')
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
            c = fgetc(dico_file);
        }
        free(buffer);

        if(c != '.')
        {
            dico* reed = create_dico();
            reed->code = code;
            reed->data = fgetc(dico_file);
            reed->left = read_dico(dico_file);
            reed->right = read_dico(dico_file);
            return reed;
        }
        return NULL;
        
    }
    return NULL;
}

void dico_to_tree(dico* d, huffman* tree)
{
    if(d != NULL && tree != NULL)
    {
        char_SLL* buffer = d->code;
        huffman* scan = tree;
        while (buffer != NULL)
        {
            if(buffer->data == '0')
            {
                if(scan->zero == NULL)
                {
                    scan->zero = create_tree();
                }
                scan = scan->zero;
            }
            else
            {
                if(scan->one == NULL)
                {
                    scan->one = create_tree();
                }
                scan = scan->one;
            }
            
            buffer = buffer->next;
        }
        
        scan->data = d->data;
        dico_to_tree(d->left, tree);
        dico_to_tree(d->right, tree);
        free(d);
    }
}

void translate(char_SLL* code, huffman* tree, FILE* output_file)
{
    huffman* buffer = tree;
    char_SLL* c = code;
    while(c != NULL)
    {
        if(c->data == '0')
        {
            buffer = buffer->zero;
        }
        else
        {
            buffer = buffer->one;
        }
        if(buffer->data != 0)
        {
            fputc(buffer->data, output_file);
            buffer = tree;
        }
        c = c->next;
    }
}

void decrypt(char* input_path, char* dico_path, char* output_path)
{
    char_SLL* code = getcode(input_path);
    FILE* dico_file = fopen(dico_path, "r");
    dico* d = read_dico(dico_file);
    fclose(dico_file);
    
    huffman* tree = create_tree();
    dico_to_tree(d, tree);

    FILE* output_file = fopen(output_path, "w");
    translate(code, tree, output_file);
    fclose(output_file);

    free_char(code);
    free_tree(tree);
}
