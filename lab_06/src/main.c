#include "handle_options.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        PRINT_COLOR(RED, "Неверное кол-во позиционных аргументов (вторым аргументом указывается файл для чтения)");
        return 2;
    }
    char file_in[LEN_FILENAME];
    strncpy(file_in, argv[1], LEN_FILENAME - 1);
    file_in[LEN_FILENAME - 1] = '\0';
    int mode = 1;

    print_task();
    node_t *root = NULL;
    while (mode)
    {
        print_menu();
        char buffer[100];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%d", &mode) != 1)
        {
            PRINT_COLOR(RED, "Ошибка чтения опции!");
            return 1;
        }
        switch (mode)
        {
        case 1 :
        {
            handle_generate_file(file_in);
            break;
        }
        case 2 :
        {
            handle_generate_tree(&root, file_in);
            break;
        }
        case 3 :
        {
            handle_export_tree(root);
            break;
        }

        case 4 :
        {
            handle_traversal(root);
            break;
        }
        case 5 :
        {
            handle_insert_node(&root);
            break;
        }
        case 6 : 
        {
            handle_delete_nodes(&root);
            break;
        }
        case 7 :
        {
            handle_compare_time(file_in);
            break;
        }
        case 8 :
        {
            handle_search_node(root);
            break;
        }
        case 9 :
        {
            handle_cleanup(file_in, &root);
            break;
        }
        case 0 :
        {
            handle_exit(file_in, root);
            return 0;
        }
        default:
            break;
        }
    }

    free_tree(root);
    clean_file(file_in);


}