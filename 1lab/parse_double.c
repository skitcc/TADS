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
        *sign = 1; // По умолчанию, знак '+'
    }
}

// Убираем незначащие нули перед точкой
int mantissa_before_dot_fill(char **input, int *mantissa, size_t *mantissa_len)
{
    // Пропускаем ведущие нули перед десятичной точкой
    while (**input == '0')
    {
        (*input)++;
    }

    // Заполняем значащие цифры перед точкой
    while (strchr("Ee.\0", **input) == NULL)
    {
        if (*mantissa_len >= MAX_LEN_MANTISSA)
            return ERROR_TOO_LONG_MANTISSA;
        
        mantissa[(*mantissa_len)++] = *((*input)++) - '0';
    }
    return 0;
}

// Убираем конечные нули после точки
int mantissa_after_dot_fill(char **input, int *mantissa, size_t *mantissa_len, int *exp_diff)
{
    int last_significant_digit = *mantissa_len; // Последняя значащая цифра

    while (strchr("Ee\0", **input) == NULL)
    {
        if (*mantissa_len >= MAX_LEN_MANTISSA) 
            return ERROR_TOO_LONG_MANTISSA;

        int digit = *((*input)++) - '0';
        mantissa[(*mantissa_len)++] = digit;
        (*exp_diff)--;  // Уменьшаем exp_diff для каждой цифры после точки

        if (digit != 0)
            last_significant_digit = *mantissa_len; // Обновляем последнюю значащую цифру
    }

    // Удаляем конечные нули
    *mantissa_len = last_significant_digit;

    return 0;
}

// Заполнение порядка (экспоненты)
void order_fill(char **input, int *exp)
{
    *exp = 0;  // Инициализируем экспоненту


    // Обрабатываем цифры экспоненты
    while (**input != '\0' && **input >= '0' && **input <= '9')
    {
        *exp = *exp * 10 + (*((*input)++) - '0');
    }
    // printf("exp_order : %d\n", *exp);
}

// Основная функция для разбора строки и извлечения мантиссы и экспоненты
int mantissa_check(char *input, double_data *data)
{
    const char pattern[] = "^[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)$";
    regex_t regex;

    // Проверка регулярного выражения
    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return ERROR_MATCHING_REG_EXPR;

    if (regexec(&regex, input, 0, NULL, 0) != 0)
        return ERROR_MATCHING_REG_EXPR;

    char *temp = input;
    data->len = 0;
    int exp_diff = 0;  // Разница порядка после точки

    // Инициализация экспоненты
    data->exp = 0;
    data->exp_sign = 1;  // Инициализируем знак экспоненты как положительный

    // Проверка знака числа
    sign_validation(&temp, &data->num_sign);

    // Обрабатываем часть до точки
    if (mantissa_before_dot_fill(&temp, data->mantissa, &data->len  ) != 0)
        return ERROR_TOO_LONG_MANTISSA;

    // Обрабатываем часть после точки
    if (*temp == '.')
    {
        temp++;
        if (mantissa_after_dot_fill(&temp, data->mantissa, &data->len, &exp_diff) != 0)
            return ERROR_TOO_LONG_MANTISSA;
    }

    // Обработка экспоненты (если есть)
    if (*temp == 'e' || *temp == 'E')
    {
        temp++;
        sign_validation(&temp, &data->exp_sign);
        order_fill(&temp, &data->exp);
    }

    // Корректировка экспоненты
    data->exp = data->exp * data->exp_sign + exp_diff;  // Корректируем экспоненту с учетом разницы порядка после точки

    // Проверка длины мантиссы
    if (data->len > MAX_LEN_MANTISSA)
        return ERROR_TOO_LONG_MANTISSA;

    // Проверка величины экспоненты
    if (abs(data->exp) > 99999)
        return TOO_LONG_EXP;

    // Отладочная информация
    printf("Mantissa: ");
    for (size_t i = 0; i < data->len; i++)
        printf("%d", data->mantissa[i]);

    printf("\nExp: %d\n", data->exp);
    return 0;
}
