#include "ht_operations.h"


unsigned hash(const char *str, int size)
{
    unsigned hash_value = 0;
    while (*str) 
        hash_value = (hash_value * 31 + *str++) % size;
    return hash_value;
}

open_ht* create_open_table(int size) 
{
    open_ht* table = (open_ht*)malloc(sizeof(open_ht));
    table->size = size;
    table->open_table = malloc(size * sizeof(char*));
    if (!table->open_table)
        return NULL;
    table->status = malloc(size * sizeof(int));
    if (!table->status)
    {
        free(table->open_table);
        return NULL;
    }
    table->comparisons = 0;

    for (int i = 0; i < size; i++) 
    {
        table->open_table[i] = NULL;
        table->status[i] = 0;
    }
    
    return table;
}


void insert_open(open_ht *table, const char *word) 
{
    unsigned int index = hash(word, table->size);
    int original_index = index;
    int i = 0;
    // printf("index = %u\n", index);
    while (table->status[index] == 1) 
    {
        index = (original_index + i) % table->size;
        i++;
    }

    table->open_table[index] = (char*)malloc(strlen(word) + 1);
    strcpy(table->open_table[index], word);
    table->status[index] = 1; 
}

// Поиск слова
char* search_open(open_ht* table, const char* word) 
{
    unsigned int index = hash(word, table->size);
    int original_index = index;
    int i = 0;

    table->comparisons = 0;

    while (table->status[index] != 0) 
    {
        table->comparisons++;
        if (table->status[index] == 1 && table->open_table[index] && strcmp(table->open_table[index], word) == 0) 
            return table->open_table[index];
        index = (original_index + i) % table->size;
        i++;
        if (i >= table->size)
            break;
    }
    return NULL;
}

// Удаление слова
void delete_open(open_ht* table, const char* word) 
{
    unsigned int index = hash(word, table->size);
    int original_index = index;
    int i = 0;

    table->comparisons = 0;

    while (table->status[index] != 0) 
    {
        table->comparisons++;
        if (table->status[index] == 1 && strcmp(table->open_table[index], word) == 0) 
        {
            free(table->open_table[index]);
            table->open_table[index] = NULL;
            table->status[index] = 2;
            return;
        }
        index = (original_index + i) % table->size;
        i++;
        if (i >= table->size)
            break;
    }
}



closed_ht* create_closed_table(int size) 
{
    closed_ht* table = (closed_ht*)malloc(sizeof(closed_ht));
    if (!table)
        return NULL;
    table->size = size;
    table->closed_table = (hash_node_t**)malloc(size * sizeof(hash_node_t*));
    if (!table->closed_table)
    {
        free(table);
        return NULL;
    }
    table->comparisons = 0;

    for (int i = 0; i < size; i++) 
        table->closed_table[i] = NULL;

    return table;
}


void insert_closed(closed_ht* table, const char* word) 
{
    unsigned int index = hash(word, table->size);
    hash_node_t* newNode = (hash_node_t*)malloc(sizeof(hash_node_t));
    strcpy(newNode->word, word);
    newNode->next = table->closed_table[index];
    table->closed_table[index] = newNode;
}


hash_node_t* search_closed(closed_ht* table, const char* word) 
{
    unsigned int index = hash(word, table->size);
    hash_node_t* node = table->closed_table[index];

    table->comparisons = 0;

    while (node) 
    {
        table->comparisons++;
        if (strcmp(node->word, word) == 0) 
            return node;
        node = node->next;
    }
    return NULL;
}


void delete_closed(closed_ht* table, const char* word) 
{
    unsigned int index = hash(word, table->size);
    hash_node_t* node = table->closed_table[index];
    hash_node_t* prev = NULL;

    table->comparisons = 0;

    while (node) {
        table->comparisons++;
        if (strcmp(node->word, word) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->closed_table[index] = node->next;
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void free_closed_table(closed_ht* table) 
{
    for (int i = 0; i < table->size; i++) 
    {
        hash_node_t* node = table->closed_table[i];
        while (node) 
        {
            hash_node_t* temp = node;
            node = node->next;
            free(temp);
        }
    }
    free(table->closed_table);
    free(table);
}



void free_open_table(open_ht* table) 
{
    for (int i = 0; i < table->size; i++) 
    {
        if (table->status[i] == 1) 
            free(table->open_table[i]);
    }
    free(table->open_table);
    free(table->status);
    free(table);
}


void read_file_to_hts(const char* filename, closed_ht* closed_table, open_ht* open_table) 
{
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) 
    {
        insert_open(open_table, word);
        insert_closed(closed_table, word);
    }

    fclose(file);
}
