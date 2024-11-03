#include "utils.h"

// Функция для инициализации стеков
void initialize_stacks(static_array_stack_t *st_arr_stack, dynamic_array_stack_t *dn_arr_stack, list_stack_t **list_stack) {
    init_static_array_stack(st_arr_stack);
    init_dynamic_array_stack(dn_arr_stack);
    *list_stack = init_list_stack();
}

// Функция для заполнения стека из выражения
void fill_stack_from_expression(const char *expr, void *stack, stack_type_t type) {
    if (type == STATIC_ARRAY || type == DYNAMIC_ARRAY)
    {
        for (int i = 0; expr[i] != '\0'; i++) {
            if (expr[i] == '(' || expr[i] == ')' || expr[i] == '{' || expr[i] == '}' || expr[i] == '[' || expr[i] == ']') {
                if (push(stack, type, expr[i]) != 0) {
                    printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                    return;
                }
            }
        }
    }

    
    printf("%sВсе скобки выражения добавлены в стек!%s\n", GREEN, RESET);
}

void fill_list(const char *expr, list_stack_t **stack)
{

    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '{' || expr[i] == '}' || expr[i] == '[' || expr[i] == ']') {
            if (push_list(stack, expr[i]) != 0) {
                printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                return;
            }
        }
    }
    
}