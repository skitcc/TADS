#include "mantiss_format.h"
short before_dot_check(char *my_double, char *format_double, size_t *i_m, size_t *ind_format, short *flag)
{
    while (my_double[*i_m] != '.' && my_double[*i_m] != '\0')
    {
        if (my_double[*i_m] - '0' && !(*flag))
        {
            *flag = *i_m;
            format_double[(*ind_format)++] = my_double[*i_m];
        }

        if (*flag && *flag != *i_m)
            format_double[(*ind_format)++] = my_double[*i_m];

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

short exp_check(char *my_double, char *format_double, size_t *i_m, size_t *ind_format, short *flag, char *sign_exp)
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
    if (strlen(my_double) - *k > MAX_ORDER || strlen(my_double) - *k == 0)
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
            if (*flag && *flag != *i_m)
                temp_str[(*temp_ind)++] = my_double[*i_m];
        }
        (*i_m)--;
    }
}


short check_mantiss(char *my_double, char *format_double)
{
    if (my_double[0] != '+' && my_double[0] != '-')
    {
        printf("Нет знака!\n");
        return WRONG_SIGN;
    }
    size_t i_m = 1;
    short m = 0, n = 0;
    short flag = 0;
    size_t ind = 1;
    format_double[0] = my_double[0];
    short db = before_dot_check(my_double, format_double, &i_m, &ind, &flag);
    if (db != 0)
        return db;

    m = i_m - flag;
    short dot = i_m;
    
    format_double[ind++] = my_double[i_m++];

    char sign_exp;
    short ec = exp_check(my_double, format_double, &i_m, &ind, &flag, &sign_exp);
    if (sign_exp != '+' && sign_exp != '-')
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
        format_double[ind++] = temp_str[i - 1];

    format_double[ind++] = 'E';
    format_double[ind++] = sign_exp;
    for (size_t i = temp_k; i < strlen(my_double); i++)
        format_double[ind++] = my_double[i];

    n = flag - dot;
    if (m + n > 30)
    {
        printf("Длина мантиссы превышает заданнную!\n");
        return TOO_MANY_DIGITS;
    }
    return EXIT_SUCCESS;
}


short check_int(char *my_int)
{
    size_t len = strlen(my_int);
    size_t i = 0;
    if (my_int[0] > '0' && my_int[0] < '9')
    {
        i = 0;
    }
    else if (my_int[0] == '+' || my_int[0] == '-')
    {
        i = 1;
    }
    else
    {
        printf("Неправильный знак в целом числе!\n");
        return WRONG_SIGN;
    }
    for (; i < len; i++)
    {
        if (my_int[i] < '0' || my_int[i] > '9')
        {
            printf("Неожиданный символ в целом числе! - %zu\n", i);
            return WRONG_CHAR;
        } 
    }
    
    return EXIT_SUCCESS;

}
