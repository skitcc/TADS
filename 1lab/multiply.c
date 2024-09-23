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

void remove_trailing_zeros(result_data *result)
{
    // Удаляем незначащие нули с конца мантиссы
    while (result->len > 1 && result->mantissa[result->len - 1] == 0)
    {
        result->len--;
    }
}

// Округление мантиссы
void round_mantissa(int *result_mas, size_t *len_arr, int *exp)
{
    if (*len_arr > SIZE_MANTISSA) {
        printf("here\n");
        size_t last_digit_pos = SIZE_MANTISSA;

        // Округляем старший разряд, если это необходимо
        if (result_mas[last_digit_pos] >= 5) {
            result_mas[last_digit_pos - 1]++;
        }

        // Переносим округление влево
        for (int i = last_digit_pos - 1; i > 0; i--) {
            if (result_mas[i] == 10) {
                result_mas[i] = 0;
                result_mas[i - 1]++;
            }
        }

        // Если старшая цифра после округления равна 10, переносим её
        if (result_mas[0] == 10) {
            result_mas[0] = 1;
            (*exp)++;
        }

        // Устанавливаем новую длину мантиссы
        *len_arr = SIZE_MANTISSA;
    }
}

// Перемножение мантисс двух чисел
void multiply_mantissas(double_data *num1, int_data *num2, result_data *result)
{
    // Временный массив для промежуточных результатов
    int temp_result[SIZE_RESULT][SIZE_RESULT] = {0};

    // Определяем длину мантисс
    size_t len1 = num1->len;
    size_t len2 = num2->len;

    // Разворачиваем массивы для удобства работы с цифрами по порядку (от младших к старшим)
    reverse_array(num1->mantissa, len1);
    reverse_array(num2->int_value, len2);

    // Умножаем мантиссы (поразрядное умножение с сохранением в матрицу)
    for (size_t i = 0; i < len1; i++)
    {
        for (size_t j = 0; j < len2; j++)
        {
            temp_result[i][i + j] += num1->mantissa[i] * num2->int_value[j];
        }
    }

    int mas_of_sums[MAX_LEN_MANTISSA * 2] = {0};  // Одномерный массив для хранения результата

    for (size_t i = 0; i < len1 + len2 - 1; i++) {
        for (size_t j = 0; j < len1; j++) {
            mas_of_sums[i] += temp_result[j][i];
        }
    }

    int carry = 0;
    for (size_t i = 0; i < len1 + len2 - 1; i++) {
        printf("mas_of_sums_i : %d\n", mas_of_sums[i]);
        int temp = mas_of_sums[i] + carry;
        mas_of_sums[i] = temp % 10;
        carry = temp / 10;
    }
    if (carry > 10)
    {
        int temp = mas_of_sums[len1 + len2 - 1] + carry;
        mas_of_sums[len1 + len2 - 1] = temp % 10;
        carry = temp / 10;
    }


    // Если остались переносы, добавляем их в конец
    size_t result_len = len1 + len2 - 1;
    printf("carry : %d\n", carry);
    while (carry > 0)
    {
        printf("while\n");
        mas_of_sums[result_len++] = carry % 10;
        carry /= 10;
        result->exp++;
        printf("exppppppp1: %d\n", result->exp);
    }
    printf("exppppppp2: %d\n", result->exp);

    // Убираем ведущие нули
    while (result_len > 1 && mas_of_sums[result_len - 1] == 0)
    {
        result_len--;
    }
    printf("exppppppp3: %d\n", result->exp);

    // printf()
    // Копируем результат в результирующую структуру
    for (size_t i = 0; i < result_len; i++)
    {
        result->mantissa[i] = mas_of_sums[i];
    }
    printf("exppppppp4: %d\n", result->exp);

    // Разворачиваем результат для корректного представления (снова от старших к младшим)
    reverse_array(result->mantissa, result_len);
    printf("exppppppp5: %d\n", result->exp);

    // Округляем мантиссу, если длина больше допустимой
    round_mantissa(result->mantissa, &result_len, &result->exp);
    printf("exppppppp6: %d\n", result->exp);

    // Записываем длину результата в структуру для дальнейшего использования
    result->len = result_len;  // Сохраняем фактическую длину результирующей мантиссы
    printf("exppppppp7: %d\n", result->exp);

    // Корректировка порядка после обработки результата
    printf("rseult_mantissa[0] : %d\n", result->mantissa[0]);
    if (result->mantissa[0] >= 10)
    {
        result->mantissa[0] /= 10;
        result->exp++;  // Увеличиваем порядок ещё на 1 при необходимости
    }
    printf("result mult exp : %d\n", result->exp);
}


// Корректировка порядка экспоненты
void adjust_exponent(double_data *num1, int_data *num2, result_data *result)
{
    // if (num1->len == 1 && num2->len == 1)
    // Рассчитываем итоговый порядок
    printf("num1->exp : %d, num1->len : %zu, num2->len - 1 : %zu\n", num1->exp, num1->len, num2->len - 1);
    int total_exp = num1->exp + num1->len + (num2->len - 1);
    result->exp_sign = (total_exp >= 0) ? 1 : -1;
    printf("total_exp : %d\n", total_exp);
    printf("result_len : %zu\n", result->len);
    result->exp += total_exp;
}


// Основная функция для умножения
void multiply(double_data *num1, int_data *num2, result_data *result)
{
    // Определение знака результата
    result->num_sign = (num1->num_sign == num2->num_sign) ? 1 : -1;

    // Умножение мантисс
    multiply_mantissas(num1, num2, result);

    // Определяем длину результата
    size_t result_len = result->len;

    printf("result_len : %zu\n", result_len);

    // Убираем незначащие нули в мантиссе
    remove_trailing_zeros(result);
    // Корректировка экспоненты
    adjust_exponent(num1, num2, result);
    
    // Вывод результата
    printf("Result Mantissa: %d * ", result->num_sign);
    for (size_t i = 0; i < result->len; i++) {
        printf("%d", result->mantissa[i]);
    }
    printf("\n");

    // Вывод экспоненты
    printf("Exp: %d\n", result->exp);
}
