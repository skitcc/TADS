#include "build_structs.h"
#include "tree_operations.h"
#include "utils.h"
#include "definitions.h"
#include "visualize_tree.h"
#include "timing.h"
#include "ht_operations.h"
#include "visualise_ht.h"
#include "print_info.h"

void print_tree_structure(avl_t *root, int level) 
{
    if (!root) return;

    for (int i = 0; i < level; i++) 
        printf("  ");
    printf("%s\n", root->value);

    print_tree_structure(root->left, level + 1);
    print_tree_structure(root->right, level + 1);
}

void print_ht_statistics(const open_ht* open_table, const closed_ht* closed_table) 
{
    printf("\n=== СТАТИСТИКА ХЕШ-ТАБЛИЦ ===\n");

    // Открытая адресация
    printf("\nХеш-таблица с ОТКРЫТОЙ адресацией:\n");
    printf("Размер таблицы: %d\n", open_table->size);
    printf("Содержимое таблицы:\n");
    for (int i = 0; i < open_table->size; i++) {
        printf("  [%d]: %s\n", i,
               (open_table->status[i] == 1) ? open_table->open_table[i] : "NULL");
    }
    printf("Количество сравнений в последней операции: %d\n", open_table->comparisons);

    // Закрытая адресация
    printf("\nХеш-таблица с ЗАКРЫТОЙ адресацией:\n");
    printf("Размер таблицы: %d\n", closed_table->size);
    printf("Содержимое таблицы:\n");
    for (int i = 0; i < closed_table->size; i++) {
        printf("  [%d]:", i);
        hash_node_t* node = closed_table->closed_table[i];
        if (!node) {
            printf(" NULL\n");
        } else {
            while (node) {
                printf(" -> %s", node->word);
                node = node->next;
            }
            printf("\n");
        }
    }
    printf("Количество сравнений в последней операции: %d\n", closed_table->comparisons);

    printf("=== КОНЕЦ СТАТИСТИКИ ===\n\n");
}



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

    printf("11111\n");
    gen_data_file(filename, size_of_file);

    struct tree_interface bst = init_tree_as_bst();
    struct tree_interface avl = init_tree_as_avl();

    open_ht *open_table = NULL;
    closed_ht *closed_table = NULL;
    print_menu();

    PRINT_COLOR(TURQ, "Введите опцию");
    int option = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &option) != 1)
    {
        return 1;
    }
    bst.root = NULL;
    avl.root = NULL;
    while (option)
    {

        switch (option)
        {
            case BUILD_TREE:
            {
                bst.root = bst.init(filename);
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
                // PRINT_COLOR(VIOLET, "Введите размер хэш-таблицы");
                // int size;
                // if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &size) != 1)
                // {
                //     PRINT_COLOR(RED, "Ошибка чтения");
                //     return 1;
                // }
                open_table = create_open_table(size_of_file + 5);
                closed_table = create_closed_table(size_of_file + 5);
                read_file_to_hts(filename, closed_table, open_table);
                PRINT_COLOR(GREEN, "Хэш-таблицы созданы и заполнены.");
                print_ht_statistics(open_table, closed_table);
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
                insert_open(open_table, value);
                insert_closed(closed_table, value);
                PRINT_COLOR(GREEN, "Слово добавлено в хэш-таблицы.");
                print_ht_statistics(open_table, closed_table);

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
                delete_open(open_table, value);
                delete_closed(closed_table, value);
                PRINT_COLOR(GREEN, "Слово удалено из хэш-таблиц.");
                print_ht_statistics(open_table, closed_table);

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

                char *open_result = search_open(open_table, value);
                hash_node_t *closed_result = search_closed(closed_table, value);

                if (open_result)
                    PRINT_COLOR(GREEN, "Слово найдено в открытой хэш-таблице!");
                else
                    PRINT_COLOR(RED, "Слово не найдено в открытой хэш-таблице!");

                if (closed_result)
                    PRINT_COLOR(GREEN, "Слово найдено в закрытой хэш-таблице!");
                else
                    PRINT_COLOR(RED, "Слово не найдено в закрытой хэш-таблице!");
                break;
            }
            case MEASURMENTS:
            {
                compare_time(filename, size_of_file);
                break;
            }
            case 0:
            {
                PRINT_COLOR(YELLOW, "Выход из программы");
                // avl.destroy(avl.root);
                // bst.destroy(bst.root);
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

    bst.destroy(bst.root);
    avl.destroy(avl.root);

    if (open_table != NULL && closed_table != NULL)
    {
        free_open_table(open_table);
        free_closed_table(closed_table);
    }

}