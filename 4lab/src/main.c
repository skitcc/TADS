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
    static_array_stack_t st_arr_stack;
    dynamic_array_stack_t dn_arr_stack;
    list_stack_t *list_stack = NULL;

    initialize_stacks(&st_arr_stack, &dn_arr_stack, &list_stack);
    
    char expr[MAX_LEN_EXPR + 1];
    int rc;
    if ((rc = read_expr(expr))) {
        return rc;
    }

    int mode = 1;
    char section = '-';

    // push_list(&list_stack, '{');
    // push_list(&list_stack, '}');
    // push_list(&list_stack, '(');

    // print_stack(list_stack, LIST);
    
    while (mode) {
        getchar();
        printf("Выберите опцию a, b, c\n");
        printf("%sa - использование стека посредством статического массива%s\n", TURQ, RESET);
        printf("%sb - использование стека посредством динамического массива%s\n", TURQ, RESET);
        printf("%sc - использование стека посредством списка%s\n", TURQ, RESET);
        printf("%st - Просмотр времени выполнения и затраченной памяти%s\n", TURQ, RESET);
        
        if (scanf("%c", &section) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            continue;
        }
        
        switch (section) {
            case 'a': {
                handle_static_stack(&st_arr_stack, expr);
                break;
            }
            case 'b': {
                handle_dynamic_stack(&dn_arr_stack, expr);
                break;
            }
            case 'c': {
                handle_list_stack(list_stack, expr);
                break;
            }
            case 't': {
                printf("Введите размер\n");
                int size = 0;
                if (!scanf("%d", &size))
                    printf("Введен неверный размер!\n");
                compare_time(size);
                break;
            }
            default:
                printf("%sОшибка: неверная опция!%s\n", RED, RESET);
                break;
        }
    }
    free_dynamic_array_stack(&dn_arr_stack);
    free_list_stack(&list_stack);

    return 0;
}