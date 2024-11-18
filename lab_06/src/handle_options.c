#include "handle_options.h"

void handle_generate_file(const char *file_in) 
{
    clean_file(file_in);
    PRINT_COLOR(VIOLET, "Введите размер генерируемого файла");
    char buffer[100];
    int len_of_nums = 0;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &len_of_nums) != 1) {
        PRINT_COLOR(RED, "Ошибка чтения размера файла");
        return;
    }
    gen_data_file(file_in, len_of_nums);
    PRINT_COLOR(GREEN, "Файл успешно заполнен данными!");
}

void handle_generate_tree(node_t **root, const char *file_in) 
{
    PRINT_COLOR(YELLOW, "Генерация дерева...");
    free_tree(*root);
    *root = build_tree_from_file(file_in);

    if (*root == NULL) {
        PRINT_COLOR(RED, "Невозможна генерация дерева, файл пуст!");
        return;
    }
    PRINT_COLOR(GREEN, "Дерево успешно сгенерировано!");
}

void handle_export_tree(node_t *root) 
{
    if (root) {
        export_to_dot(root, "./data/tree_before_del.dot");
    } else {
        PRINT_COLOR(RED, "Пустое дерево!");
    }
}

void handle_traversal(node_t *root) {
    if (!root) {
        PRINT_COLOR(RED, "Пустое дерево!");
        return;
    }
    PRINT_COLOR(YELLOW, "Префиксный обход");
    prefix_traversal(root, false);
    printf("\n");

    PRINT_COLOR(YELLOW, "Постфиксный обход");
    postfix_traversal(root, false);
    printf("\n");

    PRINT_COLOR(YELLOW, "Инфиксный обход");
    infix_traversal(root, false);


    printf("\n");
}

void handle_insert_node(node_t **root) {
    if (!root) {
        PRINT_COLOR(RED, "Пустое дерево!");
        return;
    }

    PRINT_COLOR(VIOLET, "Введите значение для вставки");
    char value[100];
    if (fgets(value, sizeof(value), stdin) == NULL) {
        PRINT_COLOR(RED, "Ошибка чтения значения!");
        return;
    }

    *root = insert(*root, value);
    export_to_dot(*root, "./data/after_insertion.dot");
}

void handle_delete_nodes(node_t **root) {
    PRINT_COLOR(VIOLET, "Введите символ для удаления");
    char target = 0;
    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "\n%c", &target) != 1) {
        PRINT_COLOR(RED, "Ошибка чтения символа для удаления!");
        return;
    }

    if (*root) {
        *root = delete_nodes_starting_with(*root, target);
        export_to_dot(*root, "./data/tree_after_del.dot");
    }
}

void handle_compare_time(const char *file_in) {
    PRINT_COLOR(YELLOW, "Сравнение времени выполнения удаления элемента в дереве и массиве...");
    if (compare_time(file_in)) {
        PRINT_COLOR(RED, "Ошибка сравнения времени.");
    }
}

void handle_search_node(node_t *root) {
    if (!root) {
        PRINT_COLOR(RED, "Дерево пустое!");
        return;
    }

    PRINT_COLOR(VIOLET, "Введите значение для поиска");
    char elem_to_search[100];

    if (fgets(elem_to_search, sizeof(elem_to_search), stdin) == NULL) {
        PRINT_COLOR(RED, "Ошибка чтения значения для поиска");
        return;
    }

    elem_to_search[strlen(elem_to_search) - 1] = '\0';
    if (search_node(root, elem_to_search) == NULL) {
        PRINT_COLOR(RED, "Элемент не найден");
    } else {
        PRINT_COLOR(GREEN, "Элемент найден");
    }
}

void handle_cleanup(const char *file_in, node_t **root) {
    clean_file(file_in);
    free_tree(*root);
    *root = NULL;
}

void handle_exit(const char *file_in, node_t *root) {
    PRINT_COLOR(YELLOW, "Выход из программы");
    free_tree(root);
    clean_file(file_in);
}
