#include "handle_stacks.h"

// Функция для обработки стека на статическом массиве
void handle_static_stack() 
{
    int mode = 1;
    removed_addresses_tracker_t tracker;
    tracker.count = 0;
    static_array_stack_t st_arr_stack;
    bool is_created = false;
    while (mode) 
    {
        print_static_menu();
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > 7) {
            printf("%sОшибка ввода!%s\n", RED, RESET);
        }

        switch (mode) {
            case 1: {
                init_static_array_stack(&st_arr_stack);
                is_created = true;
                printf("Стек на статическом массиве успешно реализован!\n");
                break;
            }
            case 2: {
                char element;
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                printf("Введите элемент для добавления:\n");
                // TODO: добавить проверку на то что стек может быть переполнен
                if (scanf(" %c", &element) == 1 && strchr(BRACES, element) != NULL) 
                {
                    push_st(&st_arr_stack, element);
                    printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                }
                else
                {
                    printf("Ожидалась скобка!\n");
                }
                break;
            }
            case 3: {
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                if (is_empty((void *)&st_arr_stack, STATIC_ARRAY))
                {
                    printf("Стек пуст!");
                    break;   
                }
                if (pop_st(&st_arr_stack, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
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
                printf("Введите выражение : \n");
                getchar();
                if (fgets(expr, MAX_LEN_EXPR + 1, stdin) == NULL)
                    printf("Ошибка ввода!\n");
                expr[strlen(expr) - 1] = '\0';
                printf("expr : %s\n", expr);
                static_array_stack_t st_stack;
                init_static_array_stack(&st_stack);
                
                if (check_brackets_st(&st_stack, STATIC_ARRAY, expr)) 

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
    bool is_created = false;
    while (mode) {
        print_dynamic_menu();
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > 7) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
        }

        switch (mode) {
            case 1: {
                is_created = true;
                init_dynamic_array_stack(&dn_arr_stack);
                printf("Стек размера 10 успешно создан!\n");
                break;
            }
            case 2: {
                char element;
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                printf("Введите элемент для добавления:\n");
                // getchar();
                if (scanf(" %c", &element) == 1 && strchr(BRACES, element) != NULL) {
                    push_dn(&dn_arr_stack, element);
                    printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                }
                else
                {
                    printf("Ожидалась скобка, элемент не добавлен на стек!\n");
                }
                break;

            }
            case 3: {

                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                if (is_empty((void *)&dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("Стек пуст!");
                    break;   
                }
                if (pop_dn(&dn_arr_stack, &tracker)) {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                if (is_empty(&dn_arr_stack, DYNAMIC_ARRAY))
                {
                    printf("%sСтек пуст!\n%s", GREEN, RESET);
                    break;
                }
                print_stack(&dn_arr_stack, DYNAMIC_ARRAY);
                break;
            }
            case 5: {
                char *expr = NULL;
                int size = 100;
                expr = malloc((size_t)size + 1);
                if (expr == NULL)
                {
                    printf("Err_allov");
                    break;
                }
                printf("Введите выражение\n");
                getchar();
                if (fgets(expr, 101, stdin) == NULL)
                    printf("Ошибка ввода!\n");
                expr[strlen(expr) - 1] = '\0';
                dynamic_array_stack_t dn_stack;
                init_dynamic_array_stack(&dn_stack);

                if (check_brackets_dn(&dn_stack, DYNAMIC_ARRAY, expr)) {
                    printf("%sСкобки расставлены правильно.%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка в расстановке скобок.%s\n", RED, RESET);
                }
                // printf("handle_capacity : %d\n", dn_stack.capacity);
                free(expr);
                break;
            }
            case 6: {
                init_dynamic_array_stack(&dn_arr_stack);
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
    bool is_created = false;
    while (mode) {
        print_list_menu();
        if (scanf("%d", &mode) != 1 || mode < 0 || mode > 7) {
            printf("%sОшибка ввода опции!%s\n", RED, RESET);
        }

        switch (mode) {
            case 1: {
                is_created = true;
                list_stack = init_list_stack();
                printf("Стек через односвязный список создан!\n");
                break;
            }
            case 2: {
                char element;
                printf("Введите элемент для добавления:\n");
                if (scanf(" %c", &element) == 1) 
                {
                    if (strchr(BRACES, element) != NULL && push_list(&list_stack, element) == EXIT_SUCCESS)
                        printf("%sЭлемент '%c' добавлен в стек!%s\n", GREEN, element, RESET);
                    else
                        printf("Ошибка при добавлении элемента!\n");
                }
                else
                {
                    printf("Ожидалась скобка, элемент не добавлен на стек!\n");
                }
                break;
            }
            case 3: {

                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
                if (is_empty((void *)list_stack, LIST))
                {
                    printf("Стек пуст!");
                    break;   
                }
                if (pop_list(&list_stack, &tracker)) 
                {
                    printf("%sЭлемент удален из стека!%s\n", GREEN, RESET);
                } else {
                    printf("%sОшибка: стек пуст!%s\n", RED, RESET);
                }
                break;
            }
            case 4: {
                if (!is_created)
                {
                    printf("Стек еще не создан!");
                    break;
                }
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
                list_stack_t *li_stack = init_list_stack();
                if (check_brackets_list(&li_stack, expr)) {
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