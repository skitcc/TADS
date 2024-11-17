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
        word[strcspn(word, "\n")] = '\0';
        root = insert(root, word);
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
    // printf("n = %d\n", word_count);
    if (word_count == -1)
        return NULL;

    *len = word_count;

    char **mas = malloc(sizeof(char *) * word_count);
    if (!mas)
    {
        fclose(file);
        return NULL;
    }
    char *word = NULL;
    size_t n = 0;
    // printf("1\n");
    for (int i = 0; i < word_count; i++)
    {
        if (getline(&word, &n, file) == -1)
        {
            free(mas);
            fclose(file);
            return NULL;
        }
        word[strcspn(word, "\n")] = '\0';
        // printf("word : %s\n", word);
        mas[i] = malloc(sizeof(char) * (strlen(word) + 1));
        if (!mas[i])
        {
            for (int k = 0; k < i; k++)
            {
                free(mas[k]);
            }
            free(mas);
            fclose(file);
            free(word);
            return NULL;
        }
        strcpy(mas[i], word);
        
    }
    fclose(file);
    free(word);

    return mas;
    
}
