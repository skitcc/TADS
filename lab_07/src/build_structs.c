#include "build_structs.h"



void *build_tree_from_file(const char *filename, int count)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    bst_t *root = NULL;

    char *word = NULL;
    size_t n = 0;
    int c = 0;
    while (getline(&word, &n, file) != -1 || c > count)
    {
        word[strcspn(word, "\r\n")] = '\0'; 
        if (strlen(word) == 0) 
        {
            free(word);
            word = NULL; 
            n = 0; 
            continue;
        }

        root = insert_bst(root, word);
        free(word); 
        word = NULL; 
        n = 0;
        c++;
    }

    fclose(file);
    free(word);

    return root;
}


struct tree_interface init_tree_as_bst() 
{
    struct tree_interface bst_interface = 
    {
        .root = NULL,
        .init = build_tree_from_file,
        .insert = (void *(*)(void *, const char *))insert_bst,
        .delete = (void *(*)(void *, char, int *))delete_nodes_starting_with_non_balanced,
        .search = (void *(*)(void *, const char *, int *))search_node_bst,
        .balance = NULL,
        .vusualise = (void (*)(void *, const char *, bool))export_to_dot,
        .destroy = (void (*)(void *))free_tree_bst
    };
    return bst_interface;
}

struct tree_interface init_tree_as_avl() 
{
    struct tree_interface avl_interface = 
    {
        .root = NULL,
        .init = NULL,
        .insert = (void *(*)(void *, const char *))insert_avl,
        .delete = (void *(*)(void *, char, int *))delete_nodes_starting_with_balanced,
        .search = (void *(*)(void *, const char *, int *))search_node_avl,
        .balance = (avl_t *(*)(bst_t *))balance_tree,
        .vusualise = (void (*)(void *, const char *, bool))export_to_dot,
        .destroy = (void (*)(void *))free_tree_avl

    };
    return avl_interface;
}

struct ht_interface init_open_table()
{
    struct ht_interface open_interface =
    {
        .root = NULL,
        .init = (void *(*)(int))create_open_table,
        .insert = (void (*)(void *, const char *))insert_open,
        .search = (void *(*)(void *, const char *))search_open,
        .delete = (void (*)(void *, const char *))delete_open,
        .destroy = (void (*)(void *))free_open_table,
        .print = (void (*)(void *))print_ht_open,
        .print_comps = (void (*)(void *))print_comparisons_open
    };
    return open_interface;
}

struct ht_interface init_closed_table()
{
    struct ht_interface closed_interface =
    {
        .root = NULL,
        .init = (void *(*)(int))create_closed_table,
        .insert = (void (*)(void *, const char *))insert_closed,
        .search = (void *(*)(void *, const char *))search_closed,
        .delete = (void (*)(void *, const char *))delete_closed,
        .destroy = (void (*)(void *))free_closed_table,
        .print = (void (*)(void *))print_ht_closed,
        .print_comps = (void (*)(void *))print_comparisons_closed
    };
    return closed_interface;
}

