#include "print.h"
#include "read.h"
#include "definitions.h"
#include "stack_operations.h"
#include "structs.h"
#include "handle_stacks.h"
#include "timing.h"

#include <stdio.h>

int main() 
{
    int mode = 1;
    char section = '-';
    
    while (mode) {
        getchar();
        printf("Выберите опцию a, b, c\n");
        printf("%sa - использование стека посредством статического массива%s\n", TURQ, RESET);
        printf("%sb - использование стека посредством динамического массива%s\n", TURQ, RESET);
        printf("%sc - использование стека посредством списка%s\n", TURQ, RESET);
        printf("%st - Просмотр времени выполнения и затраченной памяти%s\n", TURQ, RESET);
        printf("%sq - Выход%s\n", TURQ, RESET);
        
        if (scanf("%c", &section) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            continue;
        }
        
        switch (section) {
            case 'a': {
                handle_static_stack();
                break;
            }
            case 'b': {
                handle_dynamic_stack();
                break;
            }
            case 'c': {
                handle_list_stack();
                break;
            }
            case 't': {
                printf("Введите размер\n");
                int size = 0;
                if (!scanf("%d", &size))
                    printf("Введен неверный размер!\n");
                if (size % 2)
                {
                    printf("Размер должен быть четным!\n");
                    break;
                }
                compare_time(size);
                break;
            }
            case 'q' : {
                return EXIT_SUCCESS;
            }
            default:
                printf("%sОшибка: неверная опция!%s\n", RED, RESET);
                break;
        }
    }
    // free_dynamic_array_stack(&dn_arr_stack);
    // free_list_stack(&list_stack);

    return EXIT_SUCCESS;
}