#include "multiply.h"

// Переворот массива
void reverse_array(int *arr, size_t size)
{
    for (size_t i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}
    
// Функция которая удаляет незначащие нули
void remove_trailing_zeros(result_data *result)
{
    while (result->len > 1 && result->mantissa[result->len - 1] == 0)
        result->len--;
    
}

// Округление мантиссы
void round_mantissa(int *result_mas, size_t *len_arr, int *exp)
{
    if (*len_arr > SIZE_MANTISSA) 
    {
        size_t last_digit_pos = SIZE_MANTISSA;

        if (result_mas[last_digit_pos] >= 5) 
            result_mas[last_digit_pos - 1]++;

        for (int i = last_digit_pos - 1; i > 0; i--) 
        {
            if (result_mas[i] == 10) 
            {
                result_mas[i] = 0;
                result_mas[i - 1]++;
            }
        }

        if (result_mas[0] == 10) 
        {
            result_mas[0] = 1;
            (*exp)++;
        }

        *len_arr = SIZE_MANTISSA;
    }
}

// Перемножение мантисс двух чисел
void multiply_mantissas(double_data *num1, int_data *num2, result_data *result)
{
    int temp_result[SIZE_RESULT][SIZE_RESULT] = {0};

    size_t len1 = num1->len;
    size_t len2 = num2->len;

    reverse_array(num1->mantissa, len1);
    reverse_array(num2->int_value, len2);

    for (size_t i = 0; i < len1; i++)
        for (size_t j = 0; j < len2; j++)
            temp_result[i][i + j] += num1->mantissa[i] * num2->int_value[j];
        

    int mas_of_sums[MAX_LEN_MANTISSA * 2] = { 0 }; 

    for (size_t i = 0; i < len1 + len2 - 1; i++) 
        for (size_t j = 0; j < len1; j++) 
            mas_of_sums[i] += temp_result[j][i];

    int carry = 0;
    for (size_t i = 0; i < len1 + len2 - 1; i++) 
    {
        int temp = mas_of_sums[i] + carry;
        mas_of_sums[i] = temp % 10;
        carry = temp / 10;
    }
    printf("\ncarry : %d\n", carry);
    if (carry > 10)
    {
        int temp = mas_of_sums[len1 + len2 - 1] + carry;
        mas_of_sums[len1 + len2 - 1] = temp % 10;
        carry = temp / 10;
    }

    size_t result_len = len1 + len2 - 1;
    while (carry > 0)
    {
        mas_of_sums[result_len++] = carry % 10;
        carry /= 10;
        result->exp++;
    }
    reverse_array(mas_of_sums, result_len);

    while (result_len > 1 && mas_of_sums[result_len - 1] == 0)
    {
        printf("digit : %d\n",mas_of_sums[result_len - 1]);
        result_len--;
    }
    for (size_t i = 0; i < result_len; i++)
        result->mantissa[i] = mas_of_sums[i];

    printf("result_len : %zu\n", result_len);
    for (size_t i = 0; i < result_len; i++)
    {
        printf("%d ", result->mantissa[i]);
    }
    printf("\n");


    // reverse_array(result->mantissa, result_len);
    round_mantissa(result->mantissa, &result_len, &result->exp);

    result->len = result_len;  

    if (result->mantissa[0] >= 10)
    {
        result->mantissa[0] /= 10;
        result->exp++;  
    }
    printf("exp_upd : %d\n", result->exp);
}


// Корректировка порядка экспоненты
void adjust_exponent(double_data *num1, int_data *num2, result_data *result)
{
    printf("exp : %d,num1->len : %zu, num2->len - 1 : %zu\n", num1->exp, num1->len, num2->len - 1);
    int total_exp = num1->exp + num1->len + (num2->len - 1);
    result->exp_sign = (total_exp >= 0) ? 1 : -1;
    result->exp += total_exp;
}


// Основная функция для умножения
short multiply(double_data *num1, int_data *num2, result_data *result)
{
    result->num_sign = (num1->num_sign == num2->num_sign) ? 1 : -1;

    multiply_mantissas(num1, num2, result);
    remove_trailing_zeros(result);
    adjust_exponent(num1, num2, result);

    if (result->exp > 99999)
    {
        printf("Значение порядка по мудулю после умножения превышает 99999\n");
        return IMPOSSIBLE_TO_MULTIPLY_NUMBERS;
    }
    return 0;
}
