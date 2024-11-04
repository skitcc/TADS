#include "utils.h"


// Инициализация статического стека
void init_static_array_stack(static_array_stack_t *s) 
{
    s->top = -1;
}

// Инициализация динамического стека
void init_dynamic_array_stack(dynamic_array_stack_t *s) 
{
    s->top = -1;
    s->capacity = 10;
    s->data = (char *)malloc(s->capacity * sizeof(char));
    if (s->data == NULL) {
        printf("%sОшибка выделения памяти для динамического стека.%s\n", RED, RESET);
    }
}

// Инициализация стека-списка
list_stack_t *init_list_stack() 
{
    return NULL;
}

// Функция для инициализации стеков
void initialize_stacks(static_array_stack_t *st_arr_stack, dynamic_array_stack_t *dn_arr_stack, list_stack_t **list_stack) {
    init_static_array_stack(st_arr_stack);
    init_dynamic_array_stack(dn_arr_stack);
    *list_stack = init_list_stack();
}

// Функция для заполнения стека из выражения
void fill_stack_from_expression(const char *expr, void *stack, stack_type_t type) {

    if (stack == NULL) {
        printf("Ошибка: передан нулевой указатель на стек!\n");
        return;
    }
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

    
    // printf("%sВсе скобки выражения добавлены в стек!%s\n", GREEN, RESET);
}

void fill_list(const char *expr, list_stack_t **stack)
{
    if (stack == NULL) {
        printf("Ошибка: передан нулевой указатель на стек!\n");
        return;
    }
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '{' || expr[i] == '}' || expr[i] == '[' || expr[i] == ']') {
            if (push_list(stack, expr[i]) != 0) {
                printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                return;
            }
        }
    }
    
}