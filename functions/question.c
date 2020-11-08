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
