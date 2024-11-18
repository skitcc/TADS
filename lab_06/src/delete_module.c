#include "delete_module.h"


node_t *delete_nodes_starting_with(node_t *root, char start_char) 
{
    if (root == NULL)
        return NULL;

    root->left = delete_nodes_starting_with(root->left, start_char);
    root->right = delete_nodes_starting_with(root->right, start_char);

    if (tolower(root->value[0]) == tolower(start_char)) 
        return delete_node(root);

    return root;
}



int delete_elems_starts_with(const char *filename, char start_char) 
{
    FILE *input = fopen(filename, "r");
    if (!input) {
        perror("Ошибка открытия файла для чтения");
        return -1;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        perror("Ошибка создания временного файла");
        fclose(input);
        return -1;
    }

    char line[1024];
    int new_len = 0;

    while (fgets(line, sizeof(line), input)) {
        if (tolower(line[0]) != tolower(start_char)) 
        {
            fprintf(temp, "%s", line); 
            new_len++;
        }
    }

    fclose(input);
    fclose(temp);

    if (remove(filename) != 0 || rename("temp.txt", filename) != 0) {
        perror("Ошибка замены файла");
        return -1;
    }

    return new_len;
}


