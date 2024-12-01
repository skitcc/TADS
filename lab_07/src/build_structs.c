#include "build_structs.h"



void *build_tree_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    bst_t *root = NULL;

    char *word = NULL;
    size_t n = 0;
    while (getline(&word, &n, file) != -1)
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
        .traversal = (void (*)(void *, bool))prefix_traversal_bst,
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
        .traversal = (void (*)(void *, bool))prefix_traversal_avl,
        .balance = (avl_t *(*)(bst_t *))balance_tree,
        .vusualise = (void (*)(void *, const char *, bool))export_to_dot,
        .destroy = (void (*)(void *))free_tree_avl

    };
    return avl_interface;
}

