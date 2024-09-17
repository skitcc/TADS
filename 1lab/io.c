#include "io.h"

int input(char *int_num, char *double_num)
{

    printf("Введите целое число (до 40 цифр) знак опционален\n");
    printf("+---------1---------2---------3---------4\n");
    // getchar();
    if (fgets(int_num, MAX_LEN_INT_I, stdin) == NULL)
        return 1;


    
    printf("Введите вещественное число\n");
    printf("+---------1---------2---------3\n");
    // getchar();
    if (fgets(double_num, MAX_LEN_DOUBLE, stdin) == NULL)
        return 2;


    int_num[strlen(int_num) - 1] = '\0';
    double_num[strlen(double_num) - 1] = '\0';

    return 0;
    
}