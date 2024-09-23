#include "print_result.h"
void print_result(result_data *result)
{

    // Вывод знака числа
    if (result->num_sign == -1) {
        printf("-");
    } else {
        printf("+");
    }


    if (result->len == 0)
    {
        printf("0.0 E 1\n");
        return;
    }
    // Вывод 0.
    printf("0.");

    // Выводим все цифры мантиссы после первой значащей цифры
    for (size_t i = 0; i < result->len; i++) {
        printf("%d", result->mantissa[i]);
    }

    // Выводим экспоненту
    printf(" E ");
    // Выводим значение экспоненты
    printf("%d\n", result->exp);
}