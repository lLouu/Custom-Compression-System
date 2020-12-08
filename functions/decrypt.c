#include "../headers/decrypt.h"

char_SLL* getcode(FILE* input_file)
{
    if(input_file == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    
    char c = fgetc(input_file);
    if(c >= CODE_BASE || c < 0){c = 0;error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 1);}
    int decalage = (c == 0)?0:CODE_BASE - c;
    
    char_SLL** ret = (char_SLL**)malloc(sizeof(char_SLL*)), **scan = ret, **buffer = ret;
    *ret = NULL;
    c = fgetc(input_file);

    while(c != EOF)
    {
        for(int i = CODE_BASE - 1; i>=0; i--)
        {
            *scan = create_char();
            (*scan)->data = ((c >> i) & 1)?'1':'0';
            scan = &(*scan)->next;
            if(decalage == 0){buffer = &(*buffer)->next;}
            else{decalage--;}
        }
        c = fgetc(input_file);
    }
    
    free_char(*buffer);
    *buffer = NULL;

    char_SLL* temp = *ret;
    free(ret);
    return temp;
}

void dico_to_tree(dico* d, huffman** tree_ptr)
{
    if(tree_ptr == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 3);return;}
    
    if(d != NULL)
    {
        if(*tree_ptr == NULL)
        {
            *tree_ptr = create_tree();
        }
        huffman* scan = *tree_ptr;
        const char_SLL* buffer = d->code->content;
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
                if(buffer->data != '1'){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 5);}
                
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

void translate(char_SLL* code, const huffman* tree, FILE* output_file)
{
    if(output_file == NULL || tree == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 4);return;}
    
    const huffman* buffer = tree;
    char_SLL* c = code;
    
    while(c != NULL)
    {
        if(c->data == '0')
        {
            buffer = buffer->zero;
        }
        else
        {
            if(c->data != '1'){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 6);}
            buffer = buffer->one;
        }
        
        if(buffer->data != 0)
        {
            if(buffer->data == EOF){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 7);}
            fputc(buffer->data, output_file);
            buffer = tree;
        }
        char_SLL* temp = c;
        c = c->next;
        free(temp);
    }
}

void decrypt(const char* input_path, const char* output_path)
{
    FILE* output_file = fopen(output_path, "w");
    if(output_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 2);return;}

    FILE* input_file = fopen(input_path, "rb");
    if(input_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 3);fclose(output_file);return;}
    huffman* tree = read_tree(input_file);
    char_SLL* code = getcode(input_file);
    fclose(input_file);
    
    translate(code, tree, output_file);
    fclose(output_file);

    free_tree(tree);
}
