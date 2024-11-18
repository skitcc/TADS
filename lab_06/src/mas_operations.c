#include "mas_operations.h"

int search_in_file(const char *filename, const char *value) 
{
    FILE *input = fopen(filename, "r");
    if (!input) {
        perror("Ошибка открытия файла для чтения");
        return -1;
    }

    char line[1024];

    while (fgets(line, sizeof(line), input)) 
    {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, value) == 0) 
        {
            fclose(input);
            return 0;
        }
    }

    fclose(input);
    return 1;
}

void file_traversal(const char *filename) 
{
    FILE *input = fopen(filename, "r");
    if (!input) {
        return;
    }

    char line[1024];

    while (fgets(line, sizeof(line), input));
    fclose(input);
}