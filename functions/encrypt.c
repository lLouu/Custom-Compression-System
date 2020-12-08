#include "../headers/encrypt.h"

char_container* get_code(const char c, const dico* d)
{
    if(d == NULL){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    
    if(c == d->data)
    {
        char_container* ret = create_container();
        ret->content = copy(d->code->content);
        ret->size = d->code->size;
        return ret;
    }
    if(c < d->data)
    {
        return get_code(c, d->right);
    }
    return get_code(c, d->left);
}

void char_add(char_container* buffer, char_container* add)
{
    buffer->size += add->size;
    if(buffer->content == NULL)
    {
        buffer->content = copy(add->content);
        buffer->last = buffer->content;
    }
    else
    {
        buffer->last->next = copy(add->content);
    }
    
    while(buffer->last != NULL && buffer->last->next != NULL){buffer->last = buffer->last->next;}    
}

void compress(char_container* content, const char* output_path)
{
    FILE* output_file = fopen(output_path, "r");
    if(output_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 1);return;}
    char_SLL* buffer = content->content;
    huffman* tree = read_tree(output_file);
    fclose(output_file);
    output_file = fopen(output_path, "w");
    register_tree(output_file, tree);

    const int size = content->size;
    fputc(size%CODE_BASE, output_file);

    while(buffer != NULL)
    {
        char c = 0;
        for(int i = CODE_BASE-1; i>=0; i--)
        {
            if(buffer != NULL)
            {
                if(buffer->data == '1')
                {
                    c += pow(2,i);
                }
                char_SLL* temp = buffer;
                buffer = buffer->next;
                free(temp);
            }
        }

        fputc(c, output_file);
    }

    fclose(output_file);
}

void encrypt(const char* input_path, const char* output_path, int security)
{
    FILE* input_file = fopen(input_path, "r");
    if(input_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 2);return;}
    dico* d = compute_dico(input_path, output_path, security);
    char c = fgetc(input_file);
    char_container* content = create_container();
    while(c != EOF)
    {
        char_container* temp = get_code(c, d);
        char_add(content, temp);
        c = fgetc(input_file);
    }
    fclose(input_file);
    compress(content, output_path);
    free_dico(d);
}
