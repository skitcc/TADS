#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "tree_operations.h"
#include "utils.h"
#include "visualize_tree.h"
#include "delete_module.h"
#include "build_structs.h"
#include "timing.h"

int main(int argc, char *argv[])
{

    if (argc != 2)
        return 2;

    char file_in[LEN_FILENAME];
    strncpy(file_in, argv[1], LEN_FILENAME - 1);
    file_in[LEN_FILENAME - 1] = '\0';


    gen_data_file(file_in);
    
    node_t *root;
    char **mas_of_words = NULL;
    root = build_tree_from_file(file_in);

    if (root == NULL)
        return 1;


    int word_count = 0;
    mas_of_words = build_mas_from_file(file_in, &word_count);

    if (mas_of_words == NULL)
        return 2;

    printf("mas\n");
    // print_mas(mas_of_words, word_count);


    print_tree(root, 0, "root");
    debug_tree_structure(root);
    export_to_dot(root, "tree.dot");

    printf("Введите символ для удаления\n");
    char target = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "\n%c", &target) != 1)
    {
        return 1;
    }


    int new_word_count = delete_elems_starts_with(mas_of_words, word_count, target);
    
    printf("new_len : %d\n", new_word_count);
    if (new_word_count == 0)
        printf("Массив пуст!\n");
    
    // print_mas(mas_of_words, new_word_count); 

    root = delete_nodes_starting_with(root, target);


    print_tree(root, 0, "root");
    debug_tree_structure(root);

    // if (compare_time(file_in))
    // {
    //     return 5;
    // }
    

    free_tree(root);
    free_mas(mas_of_words, new_word_count);

}