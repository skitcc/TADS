#include "parse_double.h"

// Проверка знака числа
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

// Функция которая убирает незначащие нули и заполняет поле мантиссы в структуре
int mantissa_before_dot_fill(char **input, int *mantissa, size_t *mantissa_len)
{
    while (**input == '0')
        (*input)++;
    
    while (strchr("Ee.\0", **input) == NULL)
    {
        if (*mantissa_len >= MAX_LEN_MANTISSA)
        {
            printf("Длина мантиссы превышает 30 символов!\n");
            return ERROR_TOO_LONG_MANTISSA;
        }
        mantissa[(*mantissa_len)++] = *((*input)++) - '0';
    }
    return EXIT_SUCCESS;
}

// Функция которая убирает незначащие нули и заполняет поле мантиссы в структуре
int mantissa_after_dot_fill(char **input, int *mantissa, size_t *mantissa_len, int *exp_diff)
{
    int last_significant_digit = *mantissa_len;

    while (strchr("Ee\0", **input) == NULL)
    {
        if (*mantissa_len > MAX_LEN_MANTISSA) 
        {
            printf("Длина мантиссы превышает 30 символов!\n");
            return ERROR_TOO_LONG_MANTISSA;
        }

        int digit = *((*input)++) - '0';
        mantissa[(*mantissa_len)++] = digit;
        (*exp_diff)--; 
        if (digit != 0)
            last_significant_digit = *mantissa_len; 

    }

    *mantissa_len = last_significant_digit;

    return EXIT_SUCCESS;
}

// Заполнение порядка (экспоненты)
void order_fill(char **input, int *exp)
{
    *exp = 0;
    while (**input != '\0' && **input >= '0' && **input <= '9')
    {
        printf("input : %c\n", *(*input));
        if (*(*input) != '0')
            *exp = *exp * 10 + (*((*input)++) - '0');
    }
}

// Основная функция для разбора строки и извлечения мантиссы и экспоненты
int mantissa_check(char *input, double_data *data)
{
    const char pattern[] = "^[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)$";
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return ERROR_MATCHING_REG_EXPR;

    if (regexec(&regex, input, 0, NULL, 0) != 0)
    {
        printf("Вещественное число не соответствует формату\n");
        return ERROR_MATCHING_REG_EXPR;
    }
    char *temp = input;
    data->len = 0;
    int exp_diff = 0;

    data->exp = 0;
    data->exp_sign = 1;  

    sign_validation(&temp, &data->num_sign);

    if (mantissa_before_dot_fill(&temp, data->mantissa, &data->len  ) != 0)
        return ERROR_TOO_LONG_MANTISSA;
    

    if (*temp == '.')
    {
        temp++;
        if (mantissa_after_dot_fill(&temp, data->mantissa, &data->len, &exp_diff) != 0)
            return ERROR_TOO_LONG_MANTISSA;
        
    }

    if (*temp == 'e' || *temp == 'E')
    {
        temp++;
        sign_validation(&temp, &data->exp_sign);
        order_fill(&temp, &data->exp);
    }

    data->exp = data->exp * data->exp_sign + exp_diff;  
    printf("exp : %d", data->exp);

    // if (abs(data->exp) > 99999)
    // {
    //     printf("Значение порядка превышает 99999\n");
    //     return ERROR_TOO_LARGE_EXP;
    // }



    printf("\n");
    return EXIT_SUCCESS;
}
