#include "../headers/.main.h"
#include "file.h"

int main()
{
    int exit_code = 0;

    FILE* target = fopen(OTHER, "r");
    occurence*  list = read_occ(target);
    fclose(target);

    if(list != NULL && list->data == 'a')
    {
        if(list->next != NULL && list->next->data == 's')
        {
            if(list->next->next != NULL && list->next->next->data == 'e')
            {
                if(list->next->next->next != NULL && list->next->next->next->data == 't')
                {
                    if(list->next->occ == 3)
                    {
                        if(list->occ != 1)
                        {exit_code = 1;}
                    }
                    else
                        {exit_code = 2;}
                }
                else 
                    {exit_code = 3;}
            }
            else 
                {exit_code = 4;}
        }
        else 
            {exit_code = 5;}
    }
    else
        {exit_code = 6;}
    
    free_occ(list);                    


    printf("%d", exit_code);
    return exit_code;
}