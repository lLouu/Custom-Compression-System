#include "../headers/encrypt.h"

char_SLL* duplicata(char_SLL* original)
{
    if(original == NULL){return NULL;}

    char_SLL* dupli = create_char(), *scan = dupli;

    while(original != NULL)
    {
        scan->next = create_char();
        scan = scan->next;
        scan->data = original->data;
        original = original->next;
    }

    scan = dupli->next;
    free(dupli);
    return scan;
}

char_SLL* get_code(char c, dico* d)
{
    if(d == NULL)
    {
        return NULL;
    }
    if(c == d->data)
    {
        return duplicata(d->code);
    }
    if(c < d->data)
    {
        return get_code(c, d->right);
    }
    return get_code(c, d->left);
}

void char_add(char_SLL** buffer, char_SLL* add)
{
    while(*buffer != NULL)
    {
        buffer = &(*buffer)->next;
    }
    *buffer = add;
}

int size(char_SLL* c)
{
    if(c == NULL){return 0;}
    return 1 + size(c->next);
}

void compress(char_SLL* buffer, char* output_path)
{
    FILE* output_file = fopen(output_path, "w");

    fputc(size(buffer)%8, output_file);

    while(buffer != NULL)
    {
        char c = 0;
        for(int i = 7; i>=0; i--)
        {
            if(buffer != NULL)
            {
                if(buffer->data == '1')
                {
                    c += pow(2,i);
                }
                buffer = buffer->next;
            }
        }

        fputc(c, output_file);
    }

    fclose(output_file);
}

void encrypt(char* input_path, char* dico_path, char* output_path)
{
    dico* d = compute_dico(input_path, dico_path);

    FILE* input_file = fopen(input_path, "r");
    char c = fgetc(input_file);
    char_SLL* buffer = NULL;
    while(c != EOF)
    {
        printf("%c",c);
        char_SLL* temp = get_code(c, d);
        char_add(&buffer, temp);
        c = fgetc(input_file);
    }
    fclose(input_file);

    compress(buffer, output_path);

    free_dico(d);
}