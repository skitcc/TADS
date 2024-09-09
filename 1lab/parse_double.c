#include "parse_double.h"
short before_dot_check(char *my_double, char *mantissa, size_t *i_m, size_t *ind_format, short *flag)
{
    while (my_double[*i_m] != '.' && my_double[*i_m] != '\0')
    {
        if (my_double[*i_m] - '0' && !(*flag))
        {
            *flag = *i_m;
            mantissa[(*ind_format)++] = my_double[*i_m];
        }

        if (*flag && (int)*flag != (int)*i_m)
            mantissa[(*ind_format)++] = my_double[*i_m];

        if (my_double[*i_m] < '0' || my_double[*i_m] > '9')
        {
            printf("Неожиданный символ в мантиссе!\n");
            return WRONG_CHAR;
        }
        (*i_m)++;  
    }

    if (my_double[*i_m] != '.')
    {
        printf("Не найдена точка в мантиссе!\n");
        return NO_DOT;
    }

    return EXIT_SUCCESS;
}

short exp_check(char *my_double, size_t *i_m, char *sign_exp)
{
    while (my_double[*i_m] != 'E' && my_double[*i_m] != 'e' && my_double[*i_m] != '\0')
    {
        if (my_double[*i_m] < '0' || my_double[*i_m] > '9')
        {
            printf("Неожиданный символ в мантиссе! %c\n", my_double[*i_m]);
            return WRONG_CHAR;
        }
        (*i_m)++;
    }


    if (my_double[*i_m] == '\0')
    {
        printf("Не найдена экспонента в числе!\n");
        return WRONG_CHAR;
    }
    *sign_exp = my_double[++(*i_m)];
    (*i_m)--;

    return EXIT_SUCCESS;
}

short order_check(char *my_double, size_t *k)
{
    printf("order_size : %zu\n", strlen(my_double) - *k);
    if (strlen(my_double) - *k > MAX_LEN_ORDER || strlen(my_double) - *k == 0)
        return WRONG_SIZE_ORDER;

    while (my_double[*k] != '\0')
    {
        if (my_double[*k] < '0' || my_double[*k] > '9')
        {
            printf("Неожиданный символ в порядке числа!\n");
            return WRONG_CHAR;
        }
        (*k)++;
    }
    return EXIT_SUCCESS;
}

void fill_after_dot(char *my_double, char *temp_str, size_t *i_m, size_t *temp_ind, short *flag)
{
    while (my_double[*i_m] != '.' && *i_m > 0)
    {
        if (my_double[*i_m] >= '0' && my_double[*i_m] <= '9')
        {
            if (my_double[*i_m] - '0' && !(*flag))
            {
                *flag = *i_m;
                temp_str[(*temp_ind)++] = my_double[*i_m];
            }
            if (*flag && (int)*flag != (int)*i_m)
                temp_str[(*temp_ind)++] = my_double[*i_m];
        }
        (*i_m)--;
    }
}


short check_mantiss(char *my_double, double_data *whole_num)
{
    if (my_double[0] != '+' && my_double[0] != '-')
    {
        printf("Нет знака!\n");
        return WRONG_SIGN;
    }
    
    size_t i_m = 1;
    short m = 0, n = 0;
    short flag = 0;
    size_t ind = 0;
    whole_num->num_sign = my_double[0];
    short db = before_dot_check(my_double, whole_num->mantissa, &i_m, &ind, &flag);
    // printf("before dot manti : %s\n", whole_num->mantissa);
    if (db != 0)
        return db;

    m = i_m - flag;
    short dot = i_m;

    // Ставим точку
    whole_num->mantissa[ind++] = my_double[i_m++];

    short ec = exp_check(my_double, &i_m, &whole_num->exp_sign);
    if (whole_num->exp_sign != '+' && whole_num->exp_sign != '-')
    {
        printf("Неверный знак в экспоненте!\n");
        return WRONG_SIGN_EXP;
    }

    if (ec != 0)
        return ec;

    size_t k = i_m + 2;
    size_t temp_k = k;
    size_t temp_ind = 0;
    flag = 0;
    i_m--;
    char temp_str[MAX_LEN_DOUBLE + 1] = {0};

    fill_after_dot(my_double, temp_str, &i_m, &temp_ind, &flag);

    short oc = order_check(my_double, &k);
    if (oc != 0)
        return oc;

    for (size_t i = temp_ind; i > 0; i--)
        whole_num->mantissa[ind++] = temp_str[i - 1];
    size_t c = 0;
    for (size_t i = temp_k; i < strlen(my_double); i++)
        whole_num->order[c++] = my_double[i];

    n = flag - dot;
    if (m + n > 30)
    {
        printf("Длина мантиссы превышает заданнную!\n");
        return TOO_MANY_DIGITS;
    }
    return EXIT_SUCCESS;
}