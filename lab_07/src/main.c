#include "build_structs.h"
#include "tree_operations.h"
#include "utils.h"
#include "definitions.h"
#include "visualize_tree.h"
#include "timing.h"
#include "ht_operations.h"
#include "visualise_ht.h"
#include "print_info.h"


int main(void)
{
    print_task();
    PRINT_COLOR(VIOLET, "Введите файл для дальнешей обработки");
    char filename[LEN_FILENAME];
    if (fgets(filename, sizeof(filename), stdin) == NULL)
    {
        PRINT_COLOR(RED, "Ошибка ввода имени файла");
        return 1;
    }
    filename[strlen(filename) - 1] = '\0';

    PRINT_COLOR(VIOLET, "Введите размер файла для дальнешей обработки");
    char buf[100];
    int size_of_file = 0;
    if (fgets(buf, sizeof(buf), stdin) == NULL || sscanf(buf, "%d",&size_of_file) != 1 || size_of_file <= 0)
    {
        PRINT_COLOR(RED, "Ошибка ввода размера файла");
        return 1;
    }

    // gen_data_file(filename, size_of_file);

    struct tree_interface bst = init_tree_as_bst();
    struct tree_interface avl = init_tree_as_avl();

    struct ht_interface opened = init_open_table();
    struct ht_interface closed = init_closed_table();

    opened.root = NULL;
    closed.root = NULL;
    
    bst.root = NULL;
    avl.root = NULL;
    print_menu();

    PRINT_COLOR(TURQ, "Введите опцию");
    int option = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &option) != 1)
    {
        return 1;
    }


    while (option)
    {
        switch (option)
        {
            case BUILD_TREE:
            {
                bst.root = bst.init(filename, size_of_file);
                bst.vusualise(bst.root, "./data/build_non_balanced_tree.dot", true);
                avl.root = avl.balance(bst.root);
                avl.vusualise(avl.root, "./data/build_balanced_tree.dot", false);
                break;
            }
            case INSERT:
            {
                if (bst.root == NULL || avl.root == NULL)
                {
                    PRINT_COLOR(RED, "Деревья пусты!");
                    bst.destroy(bst.root);
                    avl.destroy(avl.root);
                    break;   
                }
                char value[50];
                PRINT_COLOR(VIOLET, "Введите слово для вставки");
                if (fgets(value, sizeof(value), stdin) == NULL)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                value[strcspn(value, "\n")] = '\0';
                bst.root = bst.insert(bst.root, value);
                avl.root = avl.insert(avl.root, value);

                bst.vusualise(bst.root, "./data/non_balanced_after_insertion.dot", true);
                avl.vusualise(avl.root, "./data/balanced_after_insertion.dot", false);
                break;
            }
            case DELETE:
            {
                if (bst.root == NULL || avl.root == NULL)
                {
                    PRINT_COLOR(RED, "Деревья пусты!");
                    bst.destroy(bst.root);
                    avl.destroy(avl.root);
                    break;   
                }
                PRINT_COLOR(VIOLET, "Введите символ для удаления");
                char buffer[10];
                char symbol;
                if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%c", &symbol) != 1)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                int comp_bst = 0;
                int comp_avl = 0;

                bst.root = bst.delete(bst.root, symbol, &comp_bst);
                avl.root = avl.delete(avl.root, symbol, &comp_avl);

                bst.vusualise(bst.root, "./data/non_balanced_after_delete.dot", true);
                avl.vusualise(avl.root, "./data/balanced_after_delete.dot", false);

                printf("Кол-во сравнений для BST : %d\n", comp_bst);
                printf("Кол-во сравнений для AVL : %d\n", comp_avl);
                break;
            }
            case SEARCH:
            {
                if (bst.root == NULL || avl.root == NULL)
                {
                    PRINT_COLOR(RED, "Деревья пусты!");
                    bst.destroy(bst.root);
                    avl.destroy(avl.root);
                    break;   
                }
                PRINT_COLOR(VIOLET, "Введите слово для поиска");
                char word[100];
                if (fgets(word, sizeof(word), stdin) == NULL)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                word[strcspn(word, "\n")] = '\0';
                int comp_bst = 0;
                int comp_avl = 0;

                bst.root = bst.search(bst.root, word, &comp_bst);
                avl.root = avl.search(avl.root, word, &comp_avl);

                printf("Кол-во сравнений для BST : %d\n", comp_bst);
                printf("Кол-во сравнений для AVL : %d\n", comp_avl);

                if (bst.root == NULL)
                    PRINT_COLOR(RED, "Слово не найдено в BST!");
                else    
                    PRINT_COLOR(GREEN, "Слово найдено в BST!");

                if (avl.root == NULL)
                    PRINT_COLOR(RED, "Слово не найдено в AVL!");
                else    
                    PRINT_COLOR(GREEN, "Слово найдено в AVL!");
                break;
            }
            case VISUALISE:
            {
                if (bst.root == NULL || avl.root == NULL)
                {
                    PRINT_COLOR(RED, "Деревья пусты!");
                    bst.destroy(bst.root);
                    avl.destroy(avl.root);
                    break;   
                }
                bst.vusualise(bst.root, "./data/non_balance_vis_opt.dot", true);
                avl.vusualise(avl.root, "./data/balance_vis_opt.dot", false);
                break;
            }
            case BUILD_HT:
            {
                opened.root = opened.init(size_of_file);
                closed.root = closed.init(size_of_file);
                read_file_to_hts(filename, closed.root, opened.root);
                PRINT_COLOR(GREEN, "Хэш-таблицы созданы и заполнены.");

                check_and_restructure((closed_ht *)closed.root);
                
                opened.print(opened.root);
                closed.print(closed.root);

                break;
            }
            case ADD_HT:
            {
                PRINT_COLOR(VIOLET, "Введите слово для вставки в хэш-таблицы");
                char value[50];
                if (fgets(value, sizeof(value), stdin) == NULL)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                value[strcspn(value, "\n")] = '\0';

                opened.insert(opened.root, value);
                closed.insert(closed.root, value);
                PRINT_COLOR(GREEN, "Слово добавлено в хэш-таблицы.");

                check_and_restructure((closed_ht *)closed.root);

                opened.print(opened.root);
                closed.print(closed.root);
                break;
            }
            case DELETE_HT:
            {
                PRINT_COLOR(VIOLET, "Введите слово для удаления из хэш-таблиц");
                char value[50];
                if (fgets(value, sizeof(value), stdin) == NULL)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                value[strcspn(value, "\n")] = '\0';

                opened.delete(opened.root, value);
                closed.delete(closed.root, value);

                PRINT_COLOR(GREEN, "Слово удалено из хэш-таблиц.");
                check_and_restructure((closed_ht *)closed.root);


                opened.print(opened.root);
                closed.print(opened.root);

                PRINT_COLOR(YELLOW, "Сравнения для таблицы с открытой адресацией");
                opened.print_comps(opened.root);
                PRINT_COLOR(YELLOW, "Сравнения для таблицы с закрытой адресацией");
                closed.print_comps(closed.root);
                break;
            }
            case SEARCH_HT:
            {
                PRINT_COLOR(VIOLET, "Введите слово для поиска в хэш-таблицах");
                char value[50];

                if (fgets(value, sizeof(value), stdin) == NULL)
                {
                    PRINT_COLOR(RED, "Ошибка чтения");
                    return 1;
                }
                value[strcspn(value, "\n")] = '\0';

                char *open_result = opened.search(opened.root, value);
                hash_node_t *closed_result = closed.search(closed.root, value);

                if (open_result)
                    PRINT_COLOR(GREEN, "Слово найдено в открытой хэш-таблице!");
                else
                    PRINT_COLOR(RED, "Слово не найдено в открытой хэш-таблице!");

                if (closed_result)
                    PRINT_COLOR(GREEN, "Слово найдено в закрытой хэш-таблице!");
                else
                    PRINT_COLOR(RED, "Слово не найдено в закрытой хэш-таблице!");

                PRINT_COLOR(YELLOW, "Сравнения для таблицы с открытой адресацией");
                opened.print_comps(opened.root);
                PRINT_COLOR(YELLOW, "Сравнения для таблицы с закрытой адресацией");
                closed.print_comps(closed.root);
                break;
            }
            case MEASURMENTS:
            {
                compare_time(filename, size_of_file);
                break;
            }   
            case PRINT_HTS:
            {
                if (opened.root == NULL || closed.root == NULL)
                {
                    PRINT_COLOR(RED, "Хэш таблицы пусты!\n");
                    break;
                }
                opened.print(opened.root);
                closed.print(closed.root);
                break;
            }
            case 0:
            {
                PRINT_COLOR(YELLOW, "Выход из программы");
                return 0;
                break;
            }
            default:
            {
                PRINT_COLOR(RED, "Неверная опция. Попробуйте снова.");
                break;
            }
        }
        print_menu();
        PRINT_COLOR(TURQ, "Введите опцию");
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &option) != 1)
        {
            return 1;
        }
        
    }

    if (bst.root != NULL && avl.root != NULL)
    {
        bst.destroy(bst.root);
        avl.destroy(avl.root);
    }

    if (opened.root != NULL && closed.root != NULL)
    {
        opened.destroy(opened.root);
        closed.destroy(closed.root);
    }

}