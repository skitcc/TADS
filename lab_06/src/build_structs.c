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



int get_quantity_words(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return -1; 

    int word_count = 0; 
    char *word = NULL;
    size_t n = 0;

    while (getline(&word, &n, file) != -1)
    {
        free(word);
        word = NULL;
        word_count++;
    }
    free(word);
    fclose(file);
    return word_count;

}


char **build_mas_from_file(const char *filename, int *len) 
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return NULL;

    int word_count = get_quantity_words(filename);
    if (word_count == -1) {
        fclose(file);
        return NULL;
    }

    *len = word_count;

    char **mas = malloc(sizeof(char *) * word_count);
    if (!mas) {
        fclose(file);
        return NULL;
    }

    char *word = NULL;
    size_t n = 0;
    for (int i = 0; i < word_count; i++) 
    {
        if (getline(&word, &n, file) == -1) 
        {
            free_mas(mas, i);
            fclose(file);
            free(word);
            return NULL;
        }

        word[strcspn(word, "\n")] = '\0';

        mas[i] = malloc(strlen(word) + 1);
        if (!mas[i]) 
        {
            free_mas(mas, i);
            fclose(file);
            free(word);
            return NULL;
        }

        strcpy(mas[i], word);
        free(word);
        word = NULL;
        n = 0;
    }

    fclose(file);
    free(word);

    return mas;
}

