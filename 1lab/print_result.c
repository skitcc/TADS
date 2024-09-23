#include "print_result.h"
void print_result(result_data *result)
{

    // Вывод знака числа
    if (result->num_sign == -1) {
        printf("-");
    } else {
        printf("+");
    }

    // Вывод 0.
    printf("0.");

    // Выводим все цифры мантиссы после первой значащей цифры
    for (size_t i = 0; i < result->len; i++) {
        printf("%d", result->mantissa[i]);
    }

    // Выводим экспоненту
    printf(" E ");

    result->exp *= result->exp_sign;
    result->exp += result->len;
    // Выводим значение экспоненты
    printf("%d\n", result->exp);
}