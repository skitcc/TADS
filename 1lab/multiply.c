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

// Округление мантиссы
void round_mantissa(int *result_mas, size_t *len_arr, int *exp)
{
    if (*len_arr >= MAX_LEN_MANTISSA) {
        printf("here\n");
        size_t last_digit_pos = MAX_LEN_MANTISSA;

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
        *len_arr = MAX_LEN_MANTISSA;
    }
}

// Перемножение мантисс двух чисел
void multiply_mantissas(double_data *num1, int_data *num2, result_data *result)
{
    // Временный массив для промежуточных результатов
    int temp_result[100][100] = {0};

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

    // Обрабатываем переносы
    int carry = 0;
    int flat_result[MAX_LEN_MANTISSA * 2] = {0};  // Одномерный массив для хранения результата

    for (size_t i = 0; i < len1 + len2; i++)
    {
        int sum = carry;

        // Складываем все результаты для позиции i по строкам матрицы temp_result
        for (size_t row = 0; row < len1; row++)
        {
            sum += temp_result[row][i];
        }

        // Обработка переноса
        flat_result[i] = sum % 10;
        carry = sum / 10;
    }

    // Если остались переносы, добавляем их в конец
    size_t result_len = len1 + len2;
    while (carry > 0)
    {
        flat_result[result_len++] = carry % 10;
        carry /= 10;
    }

    // Убираем ведущие нули
    while (result_len > 1 && flat_result[result_len - 1] == 0)
    {
        result_len--;
    }

    // Копируем результат в результирующую структуру
    for (size_t i = 0; i < result_len; i++)
    {
        result->mantissa[i] = flat_result[i];
    }

    // Разворачиваем результат для корректного представления (снова от старших к младшим)
    reverse_array(result->mantissa, result_len);

    // Округляем мантиссу, если длина больше допустимой
    round_mantissa(result->mantissa, &result_len, &num1->exp);

    // Записываем длину результата в структуру для дальнейшего использования
    result->len = result_len;  // Сохраняем фактическую длину результирующей мантиссы
}



// Корректировка порядка экспоненты
void adjust_exponent(double_data *num1, result_data *result)
{
    // Считаем итоговую экспоненту как сумму экспонент двух чисел
    // Экспонента результирующего числа увеличивается на количество цифр результата, вычитаем разряд
    int total_exp = num1->exp; // Учитываем длину результата относительно длины мантиссы num1

    result->exp_sign = (total_exp >= 0) ? 1 : -1;
    result->exp = abs(total_exp);
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

    // Корректировка экспоненты
    adjust_exponent(num1, result);

    // Вывод результата
    printf("Result Mantissa: %d * ", result->num_sign);
    for (size_t i = 0; i < result_len; i++) {
        printf("%d", result->mantissa[i]);
    }
    printf("\n");

    // Вывод экспоненты
    printf("Exp: %d\n", result->exp_sign * result->exp);
}
