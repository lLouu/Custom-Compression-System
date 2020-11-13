#include "../headers/decrypt.h"

char_SLL* getcode(const char* input_path)
{
    FILE* input_file = fopen(input_path, "r");
    if(input_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    
    char c = fgetc(input_file);
    if(c >= CODE_BASE || c < 0){c = 0;error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 1);}
    const int surplus = (c == 0)?0:CODE_BASE - c;
    
    char_SLL** ret = (char_SLL**)malloc(sizeof(char_SLL*)), **scan = ret;
    *ret = NULL;
    c = fgetc(input_file);

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
    int s = secure_size(*ret);
    for(int i = 0; i<s-surplus; i++)
    {
        scan = &(*scan)->next;
    }
    free_char(*scan);
    *scan = NULL;

    char_SLL* buffer = *ret;
    free(ret);
    fclose(input_file);
    if(s == -1){error(SLL_LOOP_ERROR, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    return buffer;
}

dico* read_dico(FILE* dico_file)
{
    if(dico_file == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    char c = fgetc(dico_file);
    
    if(c != EOF)
    {
        char_SLL *code = NULL, **buffer = (char_SLL**)malloc(sizeof(char_SLL*));

        while(c != '-' && c != '.' && c != EOF)
        {
            *buffer = create_char();
            if(c != '0' && c != '1'){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 2);}
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

        if(c != '.' && c != EOF)
        {
            dico* reed = create_dico();
            reed->code = code;
            reed->data = fgetc(dico_file);
            if(reed->data == EOF){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 3);}
            reed->left = read_dico(dico_file);
            reed->right = read_dico(dico_file);
            return reed;
        }
    }
    return NULL;
}

void dico_to_tree(dico* d, huffman** tree_ptr)
{
    if(tree_ptr == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 2);return;}
    
    if(d != NULL)
    {
        if(*tree_ptr == NULL)
        {
            *tree_ptr = create_tree();
        }
        huffman* scan = *tree_ptr;
        const char_SLL* buffer = d->code;
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
                if(buffer->data != '1'){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 4);}
                
                if(scan->one == NULL)
                {
                    scan->one = create_tree();
                }
                scan = scan->one;
            }
            
            buffer = buffer->next;
        }
        
        scan->data = d->data;
        dico_to_tree(d->left, tree_ptr);
        dico_to_tree(d->right, tree_ptr);
        free(d);
    }
}

void translate(const char_SLL* code, const huffman* tree, FILE* output_file)
{
    if(output_file == NULL || tree == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 3);return;}
    
    const huffman* buffer = tree;
    const char_SLL* c = code;
    
    while(c != NULL)
    {
        if(c->data == '0')
        {
            buffer = buffer->zero;
        }
        else
        {
            if(c->data != '1'){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 5);}
            buffer = buffer->one;
        }
        
        if(buffer->data != 0)
        {
            if(buffer->data == EOF){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 6);}
            fputc(buffer->data, output_file);
            buffer = tree;
        }
        c = c->next;
    }
}

void decrypt(const char* input_path, const char* dico_path, const char* output_path)
{
    char_SLL* code = getcode(input_path);
    FILE* dico_file = fopen(dico_path, "r");
    if(dico_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 2);free_char(code);return;}
    dico* d = read_dico(dico_file);
    fclose(dico_file);
    
    huffman* tree = NULL;
    dico_to_tree(d, &tree);

    FILE* output_file = fopen(output_path, "w");
    if(output_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 3);free_char(code);free_tree(tree);return;}
    translate(code, tree, output_file);
    fclose(output_file);

    free_char(code);
    free_tree(tree);
}
