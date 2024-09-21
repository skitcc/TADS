#include "parse_double.h"

void sign_validation(char sign, int *sign_struct, size_t *input_ind)
{
    if (sign == '+')
    {
        sign_struct++;
        (*input_ind)++;
    }
    if (sign == '-')
    {
        (*input_ind)++;
        sign_struct--;
    }
    else
    {
        sign_struct++;
    }
}


void mantissa_before_dot_fill(char *mantissa_input, int *mantissa_struct, size_t *input_ind, size_t *diff)
{
    if (*input_ind > 0)
        *diff = 1;
    while (strchr("Ee.\0", mantissa_input[*input_ind]) == NULL)
    {
        mantissa_struct[*input_ind - *diff] = mantissa_input[(*input_ind)] - '0';
        printf("%d ", mantissa_input[(*input_ind)] - '0');
        (*input_ind)++;
    }
    if (mantissa_input[*input_ind] != '.' || mantissa_input[*input_ind] != '\0')
    {
        (*input_ind)++;
        (*diff)++;
        return;
    }
}

void mantissa_after_dot_fill(char *mantissa_input, int *mantissa_struct, size_t *input_ind, size_t *order_diff, size_t *diff)
{
    while (strchr("Ee\0", mantissa_input[*input_ind]) == NULL)
    {

        mantissa_struct[*input_ind - *diff] = mantissa_input[(*input_ind)] - '0';
        printf("%d ", mantissa_input[(*input_ind)] - '0');
        (*input_ind)++;
        (*order_diff)++;
    }
    if (mantissa_input[*input_ind] != '\0')
    {
        (*input_ind)++;
        (*diff)++;
        return;
    }
}

void order_fill(char *order_input, int *order_struct, size_t *input_ind)
{
    size_t i = 0;
    while(strchr("\0", order_struct[*input_ind]) == NULL)
    {
        printf("here :  %d ", order_input[(*input_ind)] - '0');
        order_struct[i++] = order_input[(*input_ind)] - '0';
        (*input_ind)++;
    }
}

int mantissa_check(char *input, double_data *data)
{
    const char pattern[] = "^[+-]?([0-9]+([.][0-9]*)?([eE][+-]?[0-9]+)?|[.][0-9]+([eE][+-]?[0-9]+)?)$";
    regex_t regex;

    regcomp(&regex, pattern, REG_EXTENDED);

    if (regexec(&regex, input, 0, 0, 0) != 0)
        return ERROR_MATCHING_REG_EXPR;

    size_t input_ind = 0;
    size_t order_diff = 0;
    size_t diff_sign = 0;
    sign_validation(input[input_ind], &data->num_sign, &input_ind);
    mantissa_before_dot_fill(input, data->mantissa, &input_ind, &diff_sign);
    mantissa_after_dot_fill(input, data->mantissa, &input_ind, &order_diff, &diff_sign);


    printf("diff_sign : %zu\n", diff_sign);
    size_t len_mantiss = input_ind - diff_sign;
    if (len_mantiss > MAX_LEN_MANTISSA)
        return ERROR_TOO_LONG_MANTISSA;


    sign_validation(input[input_ind], &data->exp_sign, &input_ind);
    int len_order = (int)input_ind;
    
    order_fill(input, data->order, &input_ind);
    len_order -= input_ind;
    printf("len_order : %d\n", len_order);

    printf("len_mantiss : %zu\n", len_mantiss);
    for (size_t i = 0; i < len_mantiss; i++)
    {
        printf("%d ", data->mantissa[i]);
    }

    // printf("order : %d\n", data->order);
    printf("\n");
    return 0;

}