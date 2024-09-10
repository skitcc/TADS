#include "multiply.h"


void reverse_num(char *num)
{
    size_t len = strlen(num);
    for (size_t i = 0; i < (len / 2); i++)
    {
        char temp = num[i];
        num[i] = num[len - i - 1];
        num[len - i - 1] = temp;
    }
}

void reverse_array(int *arr, size_t size)
{
    for (size_t i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}


void remove_dot(double_data *double_num, size_t *diff)
{
    size_t len_double = strlen(double_num->mantissa) - 1;
    size_t dot_pos = strcspn(double_num->mantissa, ".");

    for (size_t i = dot_pos; i < len_double; i++)
        double_num->mantissa[i] = double_num->mantissa[i + 1];
    *diff = len_double - dot_pos;
    double_num->mantissa[len_double] = '\0';
    printf("double num mantissa : %s\n", double_num->mantissa);
}

void print_matrix(int matrix[MAX_LEN_ROW][MAX_LEN_COLUMN], size_t rows, size_t cols)
{
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_generator(double_data *double_num, int_data *int_num, result_data *result_num)
{

    size_t diff = 0;
    remove_dot(double_num, &diff);
    printf("diff = %zu\n", diff);

    reverse_num(double_num->mantissa);
    char reversed_double[MAX_LEN_MANTISSA + 1] = {0};
    strcpy(reversed_double, double_num->mantissa);

    reverse_num(int_num->int_value);
    char reversed_int[MAX_LEN_INT + 1] = {0};
    strcpy(reversed_int, int_num->int_value);


    char sign_int = int_num->num_sign;
    char sign_double = double_num->num_sign;

    if (((sign_int == '+' || sign_int == ' ') && sign_double == '-') || (sign_double == '-' && (sign_int == '+' || sign_int == ' ')))
        result_num->num_sign = '-';
    else
        result_num->num_sign = '+';
    

    int evaluated_number[MAX_LEN_MANTISSA] = {0};
    size_t len_int = strlen(reversed_int);
    size_t len_double = strlen(reversed_double);

    int matrix_of_mult[MAX_LEN_ROW][MAX_LEN_COLUMN] = {0};


    size_t len_result_arr = 0;
    size_t rows = len_double;
    size_t cols = len_int + len_double - 1;

    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            matrix_of_mult[i][j] = 0;
    

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < len_int; j++) {
            int digit_double = reversed_double[i] - '0'; 
            int digit_int = reversed_int[j] - '0';

            matrix_of_mult[i][i + j] += digit_double * digit_int;

        }
    }
    print_matrix(matrix_of_mult, rows, cols);
    matrix_solver(matrix_of_mult, rows, cols, evaluated_number, &len_result_arr);
    form_result(evaluated_number, len_result_arr, diff, result_num, double_num);
    printf("%s %s\n", reversed_double, reversed_int);

}

void separate_digit(int digit, char *str)
{
    size_t c = 0;
    while (digit != 0)
    {
        str[c++] = (digit % 10) + '0';
        digit /= 10;
    }
    reverse_num(str);
}


int form_result(int *result_mas, size_t len, size_t diff_dot, result_data *result_num, double_data *double_num)
{
    char first_num[MAX_FIRST_NUM_LEN + 1];
    separate_digit(result_mas[0], first_num);
    
    result_num->mantissa[0] = '0';
    result_num->mantissa[1] = '.';
    result_num->mantissa[2] = '\0';  

    strcat(result_num->mantissa, first_num);

    size_t cur_size_result = strlen(result_num->mantissa);
    
    for (size_t i = 1; i < len; i++)
    {
        result_num->mantissa[cur_size_result++] = result_mas[i] + '0';
    } 

    result_num->mantissa[cur_size_result] = '\0';

    size_t cur_len_mantiss = strlen(result_num->mantissa);

    if (cur_len_mantiss > MAX_LEN_MANTISS_RESULT_REAL)
        return RESULT_MANTISS_TOO_LONG;

    int new_order = atoi(double_num->order) + (int)diff_dot + (int)cur_len_mantiss - 2;

    if (new_order >= 0)
        result_num->exp_sign = '+';
    else
        result_num->exp_sign = '-';

    separate_digit(new_order, result_num->order);

    printf("diff_dot : %zu\n", diff_dot);
    printf("%c%sE%c%s\n", result_num->num_sign, result_num->mantissa, result_num->exp_sign, result_num->order);

    return 0;
}

void matrix_solver(int matrix[][MAX_LEN_COLUMN], size_t rows, size_t cols, int *result_mas, size_t *len_arr)
{
    int mas_of_sums[MAX_LEN_MANTISSA] = {0};
    for (size_t i = 0; i < cols; i++)
    {
        for (size_t j = 0; j < rows; j++)
        {
            mas_of_sums[*len_arr] += matrix[j][i];
        }
        (*len_arr)++;
    }

    for (size_t i = 0; i < (*len_arr) - 1; i++)
    {
        int elem = mas_of_sums[i];
        if (elem < 10)
            continue;
        mas_of_sums[i + 1] += (elem / 10);
        result_mas[i] = mas_of_sums[i] % 10;
    }
    
    result_mas[(*len_arr) - 1] = mas_of_sums[(*len_arr) - 1];


    for (size_t i = 0; i < *len_arr; i++)
        printf("%d ", result_mas[i]);

    reverse_array(result_mas, *len_arr);
    printf("\nresult_array : ");
    for (size_t i = 0; i < *len_arr; i++)
        printf("%d ", result_mas[i]);
    printf("\n");

}









