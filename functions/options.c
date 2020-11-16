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
        case 's':
            if(*temp != '\n'){buffer->source = temp;}
            break;
        case 'o':
            if(*temp != '\n'){buffer->out = temp;}
            break;
        case 'c':
            if(*temp != '\n'){buffer->compress_file_name = temp;}
            break;
        case 't':
            if(*temp != '\n'){buffer->tree_file_name = temp;}
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
    free(o->source);
    free(o->out);
    free(o->compress_file_name);
    free(o->tree_file_name);
    free(o);
}

char* get_compress_path(option* o)
{
    char* folder = (o->mode?o->out:o->source), *name = o->compress_file_name;
    int size = 0, size_buffer = 0;
    while(folder[size_buffer] != '\0'){size_buffer++;}
    while(name[size] != '\0'){size++;}
    size += size_buffer+1;
    char* ret = (char*)malloc((size+1)*sizeof(char));
    int i;
    for(i = 0; i<size_buffer; i++)
    {
        ret[i] = folder[i];
    }
    ret[size_buffer] = '/';
    for(i = size_buffer + 1; i<size; i++)
    {
        ret[i] = name[i - size_buffer - 1];
    }
    ret[size] = '\0';

    return ret;
}

char* get_tree_path(option* o)
{
    char* folder = (o->mode?o->out:o->source), *name = o->tree_file_name;
    int size = 0, size_buffer = 0;
    while(folder[size_buffer] != '\0'){size_buffer++;}
    while(name[size] != '\0'){size++;}
    size += size_buffer+1;
    char* ret = (char*)malloc((size+1)*sizeof(char));
    int i;
    for(i = 0; i<size_buffer; i++)
    {
        ret[i] = folder[i];
    }
    ret[size_buffer] = '/';
    for(i = size_buffer + 1; i<size; i++)
    {
        ret[i] = name[i - size_buffer - 1];
    }
    ret[size] = '\0';

    return ret;
}
