#include "print_result.h"

// Вывод результата
void print_result(result_data *result)
{
    printf("Result : ");
    if (result->num_sign == -1) 
        printf("-");
    else 
        printf("+");

    if (result->len == 0)
    {
        printf("0.0 E 1\n");
        return;
    }
    size_t save = 0;
    for (size_t i = 0; i < result->len; i++)
    {
        if (result->mantissa[i] != 0)
        {              
            save = i;
            break;
        }
    }

    printf("0.");

    for (size_t i = save; i < result->len; i++) 
        printf("%d", result->mantissa[i]);

    printf(" E ");
    printf("%d\n", (int)result->exp - (int)save);
}