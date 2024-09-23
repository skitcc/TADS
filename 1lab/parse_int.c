#include "parse_int.h"

// Функция для проверки знака числа
static void sign_validation(char **input, int *sign)
{
    if (**input == '-')
    {
        *sign = -1;
        (*input)++;
    }
    else if (**input == '+')
    {
        *sign = 1;
        (*input)++;
    }
    else
    {
        *sign = 1;
    }
}

// Заполнение целого числа с пропуском незначащих нулей
short int_fill(char **input, int *int_value, size_t *int_len)
{
    while (**input == '0')
        (*input)++;
    

    if (**input == '\0') 
    {
        int_value[(*int_len)++] = 0;
        return EXIT_SUCCESS;
    }

    while (**input >= '0' && **input <= '9')
    {
        if (*int_len >= MAX_LEN_INT)
        {
            printf("Длина целого числа превышает 40 символов!\n");
            return ERROR_TOO_LONG_INT;
        }
        int_value[(*int_len)++] = *((*input)++) - '0';
    }
    return EXIT_SUCCESS; 
}

short check_int(char *input, int_data *new_int)
{
    const char pattern[] = "^[+-]?[0-9]+$";
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return ERROR_MATCHING_REG_EXPR;

    if (regexec(&regex, input, 0, NULL, 0) != 0)
    {
        printf("Целое число не соответствует формату!\n");
        return ERROR_MATCHING_REG_EXPR;
    }
    char *temp = input;
    new_int->len = 0;

    sign_validation(&temp, &new_int->num_sign);

    if (int_fill(&temp, new_int->int_value, &new_int->len) != 0)
        return ERROR_TOO_LONG_INT;
        
    return EXIT_SUCCESS; 
}
