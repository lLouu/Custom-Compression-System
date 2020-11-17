#include "../headers/options.h"

char* s_copy(const char* original, int size)
{
    char* ret = (char*)malloc((size+1)*sizeof(char));

    for(int i = 0; i<size; i++)
    {
        if(original[i] != '\\'){ret[i] = original[i];}
        else{ret[i] = '/';}
    }
    ret[size] = '\0';

    return ret;
}

void read_option_file(option* buffer, const char* option_path)
{
    if(option_path == NULL || buffer == NULL){error(INVALID_INPUT, FILE_WEIGHT, FILE_ID, 1);return;}

    FILE* option_file = fopen(option_path, "r");
    if(option_file == NULL){error(FILE_NOT_FOUD, FILE_WEIGHT, FILE_ID, 1);return;}

    char read[100];
    for(int i = 0; i < 5; i++)
    {
        fgets(read, 100, option_file);
        int count = 0;
        while(read[count] != ':' && read[count] != '\n' && read[count] != '\0'){count++;}
        count++;
        while(read[count] == ' ' && read[count] != '\n' && read[count] != '\0'){count++;}
        
        int end = count;
        if(read[count] != '\n' && read[count] != '\0')
        {
            while(read[end]  != '\n' && read[end] != '\0'){end++;}
            if(read[end] != '\0'){read[end] = '\0';}
        }
        
        char* temp;
        if(read[count] == '\n'){error(INCOMPLETE_OPTION, FILE_WEIGHT, FILE_ID, 1); *temp = '\n';}
        else{temp = s_copy(read+count, end-count);}
        switch(*read)
        {
        case 'm':
            if(*temp != '\n')
            {
                if(*temp == '1' || *temp == 'c'){buffer->mode = 1;}
                else{buffer->mode = 0;}
                free(temp);
            }
            break;
        case 'c':
            if(*temp != '\n'){buffer->compress = temp;}
            break;
        case 'd':
            if(*temp != '\n'){buffer->decompress = temp;}
            break;
        default:
            error(CORRUPTION_ERROR, FILE_WEIGHT, FILE_ID, 1);
            break;
        }
    }
    fclose(option_file);
}

void free_option(option* o)
{
    free(o->compress);
    free(o->decompress);
    free(o);
}