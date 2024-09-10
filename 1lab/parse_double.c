#include "parse_double.h"

void char_insertion(char *str, size_t len, char to_insert)
{
    str[len - 1] = to_insert;
    for (size_t i = len - 1; i > 0; i--)
    {
        char temp = str[i];
        str[i] = str[i - 1];
        str[i - 1] = temp;
    }
}


int mantissa_check(double_data *double_num)
{
    if (double_num->num_sign == '\n')
        double_num->num_sign = '+';

    if (double_num->mantissa[0] == '.')
    {
        char_insertion(double_num->mantissa, strlen(double_num->mantissa) + 1, '0');
    }
    if (double_num->mantissa[0] > '0' && double_num->mantissa[0] < '9')
    {
        char_insertion(double_num->mantissa, strlen(double_num->mantissa) + 2, '.');
        char_insertion(double_num->mantissa, strlen(double_num->mantissa) + 2, '0');
        double_num->exp_sign += '1';
    }
    double_num->mantissa[strlen(double_num->mantissa) - 1] = '\0';
    printf("mantissa : %s\n", double_num->mantissa);
    if (double_num->mantissa[0] != '.' && (double_num->mantissa[0] < '0' && double_num->mantissa[0] > '9'))
        return MANTISS_FIRST_CHAR_ERROR;
    
    // 12345
    return 0;
    

    
}

