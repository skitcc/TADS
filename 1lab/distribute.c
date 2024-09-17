#include "distribute.h"

int mantiss_former(char *mantissa, char *src, size_t e_pos)
{
    size_t i;
    for (i = 1; i < e_pos; i++)
    {
        // if (!isdigit(src[i]) || src[i] != '.')
        // {
        //     printf("Неопознанный символ в вещ числе! - %c\n", src[i]);
        //     return 2;
        // }
        mantissa[i - 1] = src[i];
    }
    mantissa[i - 1] = '\0';
    return 0;
}

int order_former(char *order, char *src, size_t e_pos, size_t len)
{
    size_t i;
    for (i = e_pos + 2; i <= len; i++)
    {
        // if (!isdigit(src[i]))
        // {
        //     printf("Неопознанный символ в вещ числе! - %c\n", src[i]);
        //     return 2;
        // }
        order[i - e_pos  - 2] = src[i];
    }
    order[i - e_pos - 2] = '\0';
    return 0;
}


int distribute_to_double_data(double_data *double_num, char *double_str, size_t len)
{

    char *e_ptr = (strchr(double_str, 'E') != NULL) ? strchr(double_str, 'E') : strchr(double_str, 'e');
    
    size_t e_pos = (e_ptr != NULL) ? (size_t)(e_ptr - double_str) : len;

    double_num->num_sign = double_str[0];
    if (mantiss_former(double_num->mantissa, double_str, e_pos))
        return 1;
    double_num->exp_sign = double_str[e_pos + 1];
    if (order_former(double_num->order, double_str, e_pos, len))
        return 2;
    return 0;
}


void int_former(char *int_num, char *src, size_t len)
{
    size_t i = 1;
    for (; i < len; i++)
        int_num[i - 1] = src[i]; 
    
    int_num[i - 1] = '\0';
}


void distribute_to_int_data(int_data *int_num, char *int_str, size_t len)
{
    int_num->num_sign = int_str[0];
    int_former(int_num->int_value, int_str, len);
}

