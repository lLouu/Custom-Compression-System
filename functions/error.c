#include "../headers/error.h"

void location(const int file_weight, const int file_id)
{
    printf("error detection in file : ");
    switch(file_weight)
    {
    case 1:
        switch (file_id)
        {
        case 1:
            printf(ONE_ONE);
            break;
        case 2:
            printf(ONE_TWO);
            break;
        case 3:
            printf(ONE_THREE);
            break;
        default:
            printf(UNKNOWN_FILE);
            break;
        }
        break;
    case 2:
        switch (file_id)
        {
        case 1:
            printf(TWO_ONE);
            break;
        case 2:
            printf(TWO_TWO);
            break;
        default:
            printf(UNKNOWN_FILE);
            break;
        }
        break;
    case 3:
        switch (file_id)
        {
        case 1:
            printf(THREE_ONE);
            break;
        case 2:
            printf(THREE_TWO);
            break;
        default:
            printf(UNKNOWN_FILE);
            break;
        }
        break;
    case 4:
        switch (file_id)
        {
        case 1:
            printf(FOUR_ONE);
            break;
        default:
            printf(UNKNOWN_FILE);
            break;
        }
        break;
    default:
        break;
    }
    printf("\n");
}
void info(const int code_error)
{
    switch (code_error)
    {
    case SLL_LOOP_ERROR:
        printf(SLL_LOOP_MESSAGE);
        break;
    case FILE_NOT_FOUD:
        printf(FILE_NOT_FOUND_MESSAGE);
        break;
    case CORRUPTION_ERROR:
        printf(CORRUPTION_MESSAGE);
        break;
    case INVALID_INPUT:
        printf(INVALID_INPUT_MESSAGE);
        break;
    case INCOMPLETE_OPTION:
        printf(INCOMPLETE_OPTION_MESSAGE);
        break;
    case TREE_CORUPTION:
        printf(TREE_CORUPTION_MESSAGE);
        break;
    default:
        printf(UNKNOWN_ERROR);
        break;
    }
    printf("\n\n");
}

void error(const int code_error, const int file_weight, const int file_id, const int error_id)
{
    printf("error code : %d\n", (code_error*(int)pow(10,file_weight)+ file_id)*100 + error_id);
    location(file_weight, file_id);
    info(code_error);
}