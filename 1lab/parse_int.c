#include "parse_int.h"

short check_int(char *my_int, char *new_int)
{

    size_t len = strlen(my_int);


    if (len == 0)
        return EXIT_FAILURE;


    size_t start = 0;


    if (my_int[0] == '+' || my_int[0] == '-') 
    {
        new_int[0] = my_int[0];
        start = 1;
    } 
    else 
    {
        new_int[0] = '+';
        start = 0;
    }

    if (start == len) 
    {
        return EXIT_FAILURE;
    }
    


    for (size_t i = start; i < len; i++) 
    {
        if (!isdigit(my_int[i])) 
        {
            printf("Встречен неопознанный символ в целом числе!\n");
            return EXIT_FAILURE;
        }
    }


    size_t start_t = start;
    while (start_t < len && my_int[start_t] == '0') 
    {
        start_t++;
    }

    if (start_t == len) 
    {
        start_t = len - 1;
    }

    size_t new_int_len = 1; 
    for (size_t i = start_t; i < len; i++) 
    {
        new_int[new_int_len++] = my_int[i];
    }

    if (new_int_len > MAX_LEN_INT + 1) 
    {
        printf("Длина целого числа превышает 40 символов!\n");
        return EXIT_FAILURE;
    }
    
    new_int[new_int_len] = '\0'; 


    return EXIT_SUCCESS;
}