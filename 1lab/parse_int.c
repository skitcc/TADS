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
        *sign = 1; // По умолчанию, знак '+'
    }
}

// Заполнение целого числа с пропуском незначащих нулей
int int_fill(char **input, int *int_value, size_t *int_len)
{
    // Пропуск всех незначащих нулей
    while (**input == '0')
    {
        (*input)++;
    }

    // Если после всех нулей ничего не осталось, значит число - это "0"
    if (**input == '\0') 
    {
        int_value[(*int_len)++] = 0;
        return 0;
    }

    // Заполнение числа значащими цифрами
    while (**input >= '0' && **input <= '9')
    {
        if (*int_len >= MAX_LEN_INT)
            return ERROR_TOO_LONG_INT;
        int_value[(*int_len)++] = *((*input)++) - '0';
    }
    return 0; // Успех
}

short check_int(char *input, int_data *new_int)
{
    // Регулярное выражение для проверки корректности целого числа
    const char pattern[] = "^[+-]?[0-9]+$";
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return ERROR_MATCHING_REG_EXPR;

    if (regexec(&regex, input, 0, NULL, 0) != 0)
        return ERROR_MATCHING_REG_EXPR;

    char *temp = input;
    new_int->len = 0;

    // Проверка знака числа
    sign_validation(&temp, &new_int->num_sign);

    // Заполнение целого числа с пропуском незначащих нулей
    if (int_fill(&temp, new_int->int_value, &new_int->len) != 0)
        return ERROR_TOO_LONG_INT;

    // Отладочная печать
    printf("Integer: ");
    if (new_int->num_sign == -1)
        printf("-");
    for (size_t i = 0; i < new_int->len; i++)
        printf("%d", new_int->int_value[i]);

    printf("\n");

    return 0;  // Успех
}
