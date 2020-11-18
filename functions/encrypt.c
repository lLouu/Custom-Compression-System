#include "../headers/encrypt.h"

char_SLL* get_code(const char c, const dico* d)
{
    if(d == NULL){error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 1);return NULL;}
    
    if(c == d->data)
    {
        return copy(d->code);
    }
    if(c < d->data)
    {
        return get_code(c, d->right);
    }
    return get_code(c, d->left);
}

char_SLL** char_add(char_SLL** buffer, char_SLL* add)
{
    while(*buffer != NULL)
    {
        buffer = &(*buffer)->next;
    }
    *buffer = add;
    return buffer;
}

void compress(char_SLL* buffer, const char* output_path)
{
    FILE* output_file = fopen(output_path, "r");
    if(output_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 1);return;}
    huffman* tree = read_tree(output_file);
    fclose(output_file);
    output_file = fopen(output_path, "w");
    register_tree(output_file, tree);

    const int size = secure_size(buffer);
    if(size == -1){error(SLL_LOOP_ERROR, FILE_WEIGHT, FILE_ID, 1);return;}
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
    char_SLL* buffer = NULL, **scan = &buffer;
    while(c != EOF)
    {
        char_SLL* temp = get_code(c, d);
        scan = char_add(scan, temp);
        c = fgetc(input_file);
    }
    fclose(input_file);

    compress(buffer, output_path);

    free_dico(d);
}
