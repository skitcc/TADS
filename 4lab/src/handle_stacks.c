#include "handle_stacks.h"

// Функция для инициализации стеков
void initialize_stacks(static_array_stack_t *st_arr_stack, dynamic_array_stack_t *dn_arr_stack, list_stack_t **list_stack) {
    init_static_array_stack(st_arr_stack);
    init_dynamic_array_stack(dn_arr_stack);
    *list_stack = init_list_stack();
}

// Функция для заполнения стека из выражения
void fill_stack_from_expression(const char *expr, void *stack, stack_type_t type) {
    for (int i = 0; expr[i] != '\0'; i++) {
        if (expr[i] == '(' || expr[i] == ')' || expr[i] == '{' || expr[i] == '}' || expr[i] == '[' || expr[i] == ']') {
            if (push(stack, type, expr[i]) != 0) {
                printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                return;
            }
        }
    }
    printf("%sВсе скобки выражения добавлены в стек!%s\n", GREEN, RESET);
}

// Функция для обработки стека на статическом массиве
void handle_static_stack(static_array_stack_t *st_arr_stack, char *expr) {
    int mode = 1;
    
    while (mode) {
        print_static_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                fill_stack_from_expression(expr, st_arr_stack, STATIC_ARRAY);
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) {
                    if (push(st_arr_stack, STATIC_ARRAY, element) == 0) {
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                    } else {
                        printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                    }
                }
                break;
            }
            case 3: {
                if (pop(st_arr_stack, STATIC_ARRAY)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                print_stack(st_arr_stack, STATIC_ARRAY);
                break;
            }
            case 5: {
                if (!is_empty(st_arr_stack, STATIC_ARRAY)) {
                    printf("%sВнимание: стек не пуст! Хотите очистить его перед проверкой? (y/n): %s", YELLOW, RESET);
                    char choice;
                    if (scanf(" %c", &choice) == 1 && choice == 'y') {
                        init_static_array_stack(st_arr_stack);
                        printf("%sСтек очищен!%s\n", GREEN, RESET);
                    }
                }
                if (check_brackets(expr, st_arr_stack, STATIC_ARRAY)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                break;
            }
            case 6: {
                init_static_array_stack(st_arr_stack);
                printf("%sСтек очищен!%s\n", GREEN, RESET);
                break;
            }
            case 0: {
                mode = 0;
                break;
            }
            default:
                break;
        }
    }
}

// Аналогичные функции для динамического стека и стека на основе списка
void handle_dynamic_stack(dynamic_array_stack_t *dn_arr_stack, char *expr) {
    int mode = 1;

    while (mode) {
        print_dynamic_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                fill_stack_from_expression(expr, dn_arr_stack, DYNAMIC_ARRAY);
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) {
                    if (push(dn_arr_stack, DYNAMIC_ARRAY, element) == 0) {
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                    } else {
                        printf("%sОшибка при добавлении элемента!%s\n", RED, RESET);
                    }
                }
                break;
            }
            case 3: {
                if (pop(dn_arr_stack, DYNAMIC_ARRAY)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                print_stack(dn_arr_stack, DYNAMIC_ARRAY);
                break;
            }
            case 5: {
                if (!is_empty(dn_arr_stack, DYNAMIC_ARRAY)) {
                    printf("%sВнимание: стек не пуст! Хотите очистить его перед проверкой? (y/n): %s", YELLOW, RESET);
                    char choice;
                    if (scanf(" %c", &choice) == 1 && choice == 'y') {
                        free_dynamic_array_stack(dn_arr_stack);
                        init_dynamic_array_stack(dn_arr_stack);
                        printf("%sСтек очищен!%s\n", GREEN, RESET);
                    }
                }
                if (check_brackets(expr, dn_arr_stack, DYNAMIC_ARRAY)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                break;
            }
            case 6: {
                init_dynamic_array_stack(dn_arr_stack);
                printf("%sСтек очищен!%s\n", GREEN, RESET);
                break;
            }
            case 0: {
                mode = 0;
                break;
            }
            default:
                break;
        }
    }
}

void handle_list_stack(list_stack_t *list_stack, char *expr) {
    int mode = 1;

    while (mode) {
        print_list_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                fill_stack_from_expression(expr, list_stack, LIST);
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) {
                    push(&list_stack, LIST, element);
                    printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                }
                break;
            }
            case 3: {
                if (pop(&list_stack, LIST)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                print_stack(list_stack, LIST);
                break;
            }
            case 5: {
                if (!is_empty(list_stack, LIST)) {
                    printf("%sВнимание: стек не пуст! Хотите очистить его перед проверкой? (y/n): %s", YELLOW, RESET);
                    char choice;
                    if (scanf(" %c", &choice) == 1 && choice == 'y') {
                        free_list_stack(&list_stack);
                        list_stack = init_list_stack();
                        printf("%sСтек очищен!%s\n", GREEN, RESET);
                    }
                }
                if (check_brackets(expr, list_stack, LIST)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                break;
            }
            case 6: {
                free_list_stack(&list_stack);
                list_stack = init_list_stack();
                printf("%sСтек очищен!%s\n", GREEN, RESET);
                break;
            }
            case 0: {
                mode = 0;
                break;
            }
            default:
                break;
        }
    }
}