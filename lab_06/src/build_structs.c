#include "build_structs.h"



node_t *build_tree_from_file(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    node_t *root = NULL;

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

        root = insert(root, word);
        free(word); 
        word = NULL; 
        n = 0;
    }

    fclose(file);
    free(word);

    return root;
}
