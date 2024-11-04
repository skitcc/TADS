#include "handle_stacks.h"

// Функция для обработки стека на статическом массиве
void handle_static_stack() 
{
    int mode = 1;
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    static_array_stack_t st_arr_stack;
    
    while (mode) 
    {
        print_static_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                init_static_array_stack(&st_arr_stack);
                printf("Стек на статическом массиве успешно реализован!\n");
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) {
                    if (push(&st_arr_stack, STATIC_ARRAY, element) == 0) {
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                    } else {
                        printf("%sОшибка: стек переполнен!%s\n", RED, RESET);
                    }
                }
                break;
            }
            case 3: {
                if (pop(&st_arr_stack, STATIC_ARRAY, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (is_empty(&st_arr_stack, STATIC_ARRAY))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(&st_arr_stack, STATIC_ARRAY);
                break;
            }
            case 5: {
                printf("Стек реализован через статический массив, размер 1000\n");
                char *expr = NULL;
                size_t size = 1000;
                expr = malloc(size + 1);
                if (expr == NULL)
                {
                    printf("Err_allov");
                    break;
                }
                getchar();
                if (fgets(expr, MAX_LEN_EXPR + 1, stdin) == NULL)
                    printf("Ошибка ввода!\n");
                expr[strlen(expr) - 1] = '\0';
                static_array_stack_t st_stack;
                init_static_array_stack(&st_stack);
                if (check_brackets(&st_stack, STATIC_ARRAY, expr)) 

                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                
                else 
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                free(expr);
                break;
            }
            case 6: {
                init_static_array_stack(&st_arr_stack);
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
void handle_dynamic_stack() 
{
    int mode = 1;
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    dynamic_array_stack_t dn_arr_stack;
    printf("Введите размер стека от 1 - 10000\n");
    int size = 0;
    if (scanf("%d", &size) != 1)
        printf("Ошибка ввода размера стека!\n");

    while (mode) {
        print_dynamic_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                init_dynamic_array_stack(&dn_arr_stack, size);
                printf("Стек размера %d успешно создан!\n", size);
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления: ");
                if (scanf(" %c", &element) == 1) {
                    if (push(&dn_arr_stack, DYNAMIC_ARRAY, element) == 0) {
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                    } else {
                        printf("%sОшибка при добавлении элемента!%s\n", RED, RESET);
                    }
                }
                break;
            }
            case 3: {
                if (pop(&dn_arr_stack, DYNAMIC_ARRAY, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (is_empty(&dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(&dn_arr_stack, DYNAMIC_ARRAY);
                break;
            }
            case 5: {
                printf("Введите размер стека от 1 - 10000\n");
                int size = 0;
                if (scanf("%d", &size) != 1)
                {
                    printf("Ошибка ввода размера стека!\n");
                    break;
                }
                char *expr = NULL;
                expr = malloc((size_t)size + 1);
                if (expr == NULL)
                {
                    printf("Err_allov");
                    break;
                }
                printf("Введите выражение\n");
                if (fgets(expr, MAX_LEN_EXPR + 1, stdin) == NULL)
                    printf("Ошибка ввода!\n");
                expr[strlen(expr) - 1] = '\0';
                dynamic_array_stack_t dn_stack;
                init_dynamic_array_stack(&dn_stack, size);

                if (check_brackets(&dn_stack, DYNAMIC_ARRAY, expr)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                free(expr);
                break;
            }
            case 6: {
                init_dynamic_array_stack(&dn_arr_stack, size);
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

void handle_list_stack() 
{
    int mode = 1;
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    list_stack_t *list_stack;
    while (mode) {
        print_list_menu();
        if (scanf("%d", &mode) != 1) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
            return;
        }

        switch (mode) {
            case 1: {
                list_stack = init_list_stack();
                printf("Стек через односвязный список создан!\n");
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

                char *expr = NULL;
                size_t size = 1000;
                expr = malloc(size + 1);
                if (expr == NULL)
                {
                    printf("Err_allov");
                    break;
                }
                printf("Введите выражение\n");
                getchar();
                if (fgets(expr, MAX_LEN_EXPR + 1, stdin) == NULL)
                    printf("Ошибка ввода!\n");
                expr[strlen(expr) - 1] = '\0';

                if (check_brackets_list(expr)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                free(expr);
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