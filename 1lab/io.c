#include "io.h"

int input(int_data *int_num, double_data *double_num)
{

    printf("Введите знак целого числа или нажмите enter\n");
    if (scanf("%c", &int_num->num_sign) != 1)
        return INPUT_NUM_SIGN_ERROR;


    printf("Введите целоe число\n");
    getchar();
    if (fgets(int_num->int_value, MAX_LEN_INT_I, stdin) == NULL)
        return INPUT_INT_ERROR;


    int_num->int_value[strlen(int_num->int_value) - 1] = '\0';


    printf("Введите знак вещественного числа или нажмите enter\n");
    if (scanf("%c", &double_num->num_sign) != 1)
        return INPUT_NUM_SIGN_ERROR;
    
    printf("Введите мантиссу числа\n");
    getchar();

    if (fgets(double_num->mantissa, MAX_LEN_MANTISSA_I, stdin) == NULL)
        return INPUT_MANTISSA_ERROR;

    printf("Введите знак порядка или нажмите enter\n");
    if (scanf("%c", &double_num->exp_sign) != 1)
        return INPUT_SIGN_EXP_ERROR;
    
    printf("Введите порядок числа\n");
    getchar();

    if (fgets(double_num->order, MAX_LEN_ORDER_I, stdin) == NULL)
        return INPUT_ORDER_ERROR;


    double_num->mantissa[strlen(double_num->mantissa) - 1] = '\0';
    double_num->order[strlen(double_num->order) - 1] = '\0';

    return 0;
    
}