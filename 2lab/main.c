#include "definitions.h"
#include "struct.h"
#include "input.h"
#include "operations.h"
#include "sort.h"
#include "show_info.h"
#include "time_calc.h"

#include <stdio.h>

int main(void)
{
    int quantity_of_structs = 0;
    desc_t arr[MAX_LEN_STRUCTURES];
    keys_t keys[MAX_LEN_STRUCTURES];

    show_options();

    int mode = 0;
    printf("Введите опцию: ");

    while (scanf("%d", &mode) != 1 || (mode < 0 || mode > 10)) {
        printf("%sОшибка ввода опции! Введите правильное значение от 0 до 10.%s\n", RED, RESET);
        while (getchar() != '\n');
        printf("Введите опцию: ");
    }

    int code_return = 0;
    
    while (mode)  
    {
        switch (mode)
        {
            case 0:
                printf("Выход из программы\n");
                return 1;
            case 1:
                code_return = load_data(arr, &quantity_of_structs, keys);
                break;
            case 2:
                print_struct(arr, quantity_of_structs);
                break;
            case 3:
                code_return = add_data(arr, &quantity_of_structs, keys);
                break;
            case 4:
                code_return = delete_data(arr, &quantity_of_structs, keys);
                break;
            case 5:
                code_return = print_task_version(arr, quantity_of_structs);
                break;
            case 6:
                code_return = bubble_sort_structs(arr, quantity_of_structs);
                break;
            case 7:
                code_return = qsort_structs(arr, quantity_of_structs);
                break;
            case 8:
                code_return = qsort_keys(keys, quantity_of_structs);
                print_keys(keys, quantity_of_structs);
                print_struct(arr, quantity_of_structs);
                break;
            case 9:
                code_return = qsort_keys(keys, quantity_of_structs);
                print_structs_by_keys(arr, keys, quantity_of_structs);
                break;
            case 10:
                compare_sorts();
                break;
            default:
                printf("Выбранная опция недоступна!\n");
        }

        if (code_return) {
            printf("%sПри выполнении опции произошла ошибка!%s\n", RED, RESET);
        }

        show_options();
        
        printf("\nВведите опцию: ");
        
        while (scanf("%d", &mode) != 1 || (mode < 0 || mode > 10)) {
            printf("%sОшибка ввода опции! Введите правильное значение от 0 до 10.%s\n", RED, RESET);
            while (getchar() != '\n');  
            printf("Введите опцию: ");
        }
    }

    return 0;
}
