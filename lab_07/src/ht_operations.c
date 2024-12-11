#include "ht_operations.h"



#define FNV_OFFSET_BASIS 0x84222325
#define FNV_PRIME 0x01000193

static int hash(const char *str, int size) 
{
    unsigned long hash_value = FNV_OFFSET_BASIS;
    const unsigned int prime = 53;

    for (size_t i = 0; i < strlen(str); i++) 
    {
        hash_value ^= (unsigned long)str[i];
        hash_value *= FNV_PRIME;
    }

    hash_value %= size;

    return (int)hash_value;
}

void *create_open_table(int size) 
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
    table->count = 0;
    for (int i = 0; i < size; i++) 
    {
        table->open_table[i] = NULL;
        table->status[i] = 0;
    }
    
    return table;
}


static void resize_table(open_ht *table) 
{
    int new_size = table->size + 5;
    char **new_open_table = (char **)malloc(new_size * sizeof(char *));
    int *new_status = (int *)malloc(new_size * sizeof(int));
    memset(new_status, 0, new_size * sizeof(int));

    for (int i = 0; i < table->size; i++) 
    {
        if (table->status[i] == 1) 
        {
            int new_index = hash(table->open_table[i], new_size);
            int original_new_index = new_index;
            int j = 0;
            while (new_status[new_index] == 1) 
            {
                new_index = (original_new_index + j) % new_size;
                j++;
            }
            new_open_table[new_index] = table->open_table[i];
            new_status[new_index] = 1;
        }
    }

    free(table->open_table);
    free(table->status);
    table->open_table = new_open_table;
    table->status = new_status;
    table->size = new_size;
    table->count = 0;
}


void insert_open(void *root, const char *word) 
{
    open_ht *table = root;
    if (table->count >= table->size)
    {
        resize_table(table);
    }
    unsigned int index = hash(word, table->size);
    int original_index = index;
    int i = 0;
    while (table->status[index] == 1) 
    {
        index = (original_index + i) % table->size;
        i++;
    }

    table->open_table[index] = (char*)malloc(strlen(word) + 1);
    strcpy(table->open_table[index], word);
    table->status[index] = 1; 
    table->count++;
}

void* search_open(void *root, const char* word) 
{
    open_ht *table = root;
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

void delete_open(void *root, const char* word) 
{
    open_ht *table = root;
    int index = hash(word, table->size);
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

int count_collisions(hash_node_t *node) 
{
    int count = 0;
    while (node) {
        count++;
        node = node->next;
    }
    return count;
}

void restructure_table(closed_ht *ht) 
{
    int new_size = ht->size * 2;
    hash_node_t **new_table = malloc(new_size * sizeof(hash_node_t *));
    for (int i = 0; i < new_size; i++) 
        new_table[i] = NULL;

    for (int i = 0; i < ht->size; i++) 
    {
        hash_node_t *node = ht->closed_table[i];
        while (node) {
            hash_node_t *next = node->next;
            unsigned int new_index = hash(node->word, new_size);
            node->next = new_table[new_index];
            new_table[new_index] = node;
            node = next;
        }
    }

    free(ht->closed_table);
    ht->closed_table = new_table;
    ht->size = new_size;
}

void check_and_restructure(closed_ht *ht) 
{
    for (int i = 0; i < ht->size; i++) {
        if (count_collisions(ht->closed_table[i]) > 3) 
        {
            restructure_table(ht);
            return;
        }
    }
}

void *create_closed_table(int size) 
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


void insert_closed(void *root, const char* word) 
{
    closed_ht *table = root;

    unsigned int index = hash(word, table->size);
    hash_node_t* newNode = (hash_node_t*)malloc(sizeof(hash_node_t));
    strcpy(newNode->word, word);
    newNode->next = table->closed_table[index];
    table->closed_table[index] = newNode;
}


void *search_closed(void *root, const char* word) 
{
    closed_ht *table = root;
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


void delete_closed(void *root, const char* word) 
{
    closed_ht *table = root;
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

void free_closed_table(void *root) 
{
    closed_ht *table = root;
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


void free_open_table(void *root) 
{
    open_ht *table = root;
    for (int i = 0; i < table->size; i++) 
    {
        if (table->status[i] == 1) 
            free(table->open_table[i]);
    }
    free(table->open_table);
    free(table->status);
    free(table);
}

void print_comparisons_open(void *root)
{
    open_ht *table = root;
    printf("Кол-во сравнений : %d\n", table->comparisons);
}

void print_comparisons_closed(void *root)
{
    closed_ht *table = root;
    printf("Кол-во сравнений : %d\n", table->comparisons);
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

void print_ht_open(void *root)
{
    open_ht *open_table = root;
    printf("\nХеш-таблица с ОТКРЫТОЙ адресацией:\n");
    printf("Размер таблицы: %d\n", open_table->size);
    printf("Содержимое таблицы:\n");
    for (int i = 0; i < open_table->size; i++) {
        printf("  [%d]: %s\n", i,
               (open_table->status[i] == 1) ? open_table->open_table[i] : "NULL");
    }
}
void print_ht_closed(void *root)
{
    closed_ht *closed_table = root;
    printf("\nХеш-таблица с ЗАКРЫТОЙ адресацией:\n");
    printf("Размер таблицы: %d\n", closed_table->size);
    printf("Содержимое таблицы:\n");
    for (int i = 0; i < closed_table->size; i++) {
        printf("  [%d]:", i);
        hash_node_t* node = closed_table->closed_table[i];
        if (!node) {
            printf(" NULL\n");
        } else {
            while (node) {
                printf(" -> %s", node->word);
                node = node->next;
            }
            printf("\n");
        }
    }
}
