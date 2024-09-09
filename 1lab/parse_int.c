#include "parse_int.h"

short check_int(char *my_int, int_data *whole_num)
{
    size_t len = strlen(my_int);
    size_t i = 0;
    if (my_int[0] > '0' && my_int[0] < '9')
    {
        i = 0;
        whole_num->num_sign = ' ';
    }
    else if (my_int[0] == '+')
    {
        whole_num->num_sign = '+';
        i = 1;
    }
    else if (my_int[0] == '-')
    {
        whole_num->num_sign = '-';
        i = 1;
    }
    else
    {
        printf("Неправильный знак в целом числе!\n");
        return WRONG_SIGN;
    }
    size_t c = 0;
    for (; i < len; i++)
    {
        if (my_int[i] < '0' || my_int[i] > '9')
        {
            printf("Неожиданный символ в целом числе! - %zu\n", i);
            return WRONG_CHAR;
        }
        whole_num->int_value[c++] = my_int[i]; 
    }
    
    return EXIT_SUCCESS;

}