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
void sort_occ(occurence** list) 
{
    if(*list != NULL)
    {
        int cond = 1;
        occurence **s_buffer, *d_buffer;
        while(cond)
        {
            cond = 0;
            s_buffer = list;
            while((*s_buffer)->next != NULL)
            {
                if((*s_buffer)->occ < (*s_buffer)->next->occ)
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
void free_occ(occurence* list)
{
    if(list != NULL)
    {
        free_occ(list->next);
        free(list);
    }
}
