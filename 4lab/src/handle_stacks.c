#include "handle_stacks.h"

// Функция для обработки стека на статическом массиве
void handle_static_stack(static_array_stack_t *st_arr_stack, char *expr) {
    int mode = 1;
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    
    while (mode) 
    {
        print_static_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                if (!is_empty(st_arr_stack, STATIC_ARRAY))
                {
                    printf("%sСтек не пустой!%s\n", RED, RESET);
                    break;
                }
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
                if (pop(st_arr_stack, STATIC_ARRAY, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (is_empty(st_arr_stack, STATIC_ARRAY))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(st_arr_stack, STATIC_ARRAY);
                break;
            }
            case 5: {

                if (is_empty(st_arr_stack, STATIC_ARRAY))
                {
                    printf("%sСтек пустой, проверка не возможна!%s\n", RED, RESET);
                    break;
                }
                if (check_brackets(st_arr_stack, STATIC_ARRAY)) {
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
            case 7: {
                if (tracker.count == 0)
                    printf("%sСписок удаленных адресов пуст!%s", GREEN, RESET);
                printf("Список удаленных адресов\n");
                for (int i = 0; i < tracker.count; i++)
                {
                    printf("Удаленный адрес %d - %p\n", i + 1, (char *)tracker.removed_addresses[i]);
                }
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
    removed_addresses_tracker_t tracker;
    tracker.count = 0;

    while (mode) {
        print_dynamic_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                if (!is_empty(dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("%sСтек не пустой!%s\n", RED, RESET);
                    break;
                }
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
                if (pop(dn_arr_stack, DYNAMIC_ARRAY, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (is_empty(dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(dn_arr_stack, DYNAMIC_ARRAY);
                break;
            }
            case 5: {
                if (is_empty(dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("%sСтек пустой, проверка не возможна!%s\n", RED, RESET);
                    break;
                }
                if (check_brackets(dn_arr_stack, DYNAMIC_ARRAY)) {
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
            case 7: {
                if (tracker.count == 0)
                    printf("%sСписок удаленных адресов пуст!%s", GREEN, RESET);
                printf("Список удаленных адресов\n");
                for (int i = 0; i < tracker.count; i++)
                {
                    printf("Удаленный адрес %d - %p\n", i + 1, (char *)tracker.removed_addresses[i]);
                }
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
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    while (mode) {
        print_list_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                if (!is_empty(list_stack, LIST))
                {
                    printf("%sСтек не пустой!\n%s", GREEN, RESET);
                    break;
                }
                fill_list(expr, &list_stack);
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) 
                {
                    if (push_list(&list_stack, element) == EXIT_SUCCESS)
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                }
                break;
            }
            case 3: {
                if (pop_list(&list_stack, &tracker)) 
                {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (is_empty(list_stack, LIST))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(list_stack, LIST);
                break;
            }
            case 5: {
                if (check_brackets_list(list_stack)) {
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
            case 7: {
                if (tracker.count == 0)
                    printf("%sСписок удаленных адресов пуст!%s", GREEN, RESET);
                printf("Список удаленных адресов\n");

                for (int i = 0; i < tracker.count; i++)
                {
                    printf("Удаленный адрес %d - %p\n", i + 1, (char *)tracker.removed_addresses[i]);
                }
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