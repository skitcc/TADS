#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 100
#define DELETED_NODE (void*)-1 // Специальный маркер для удалённых ячеек

// Структура для представления элемента таблицы с цепочками (закрытая адресация)
typedef struct HashNode 
{
    char word[MAX_WORD_LENGTH];
    struct HashNode* next;
} HashNode;

// Структура для представления хеш-таблицы
typedef struct HashTable {
    int size;
    HashNode** table;       // Для закрытой адресации
    char** openTable;       // Для открытой адресации
    int* status;            // Массив статусов для открытой адресации (0 - пусто, 1 - занят, 2 - удалено)
    int comparisons;        // Подсчёт сравнений
} HashTable;

// Хеш-функция
unsigned int hash(const char* str, int size) {
    unsigned int hashValue = 0;
    while (*str) {
        hashValue = (hashValue << 5) + *str++;
    }
    return hashValue % size;
}

// Создание хеш-таблицы для закрытой и открытой адресации
HashTable* createTable(int size) {
    HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));
    newTable->size = size;
    newTable->table = (HashNode**)malloc(size * sizeof(HashNode*));
    newTable->openTable = (char**)malloc(size * sizeof(char*));
    newTable->status = (int*)malloc(size * sizeof(int));
    newTable->comparisons = 0;

    // Инициализация для открытой адресации
    for (int i = 0; i < size; i++) {
        newTable->openTable[i] = NULL;
        newTable->status[i] = 0; // 0 - пусто, 1 - занято, 2 - удалено
    }

    // Инициализация для закрытой адресации
    for (int i = 0; i < size; i++) {
        newTable->table[i] = NULL;
    }

    return newTable;
}

// Вставка слова с открытой адресацией
void insertOpen(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    int originalIndex = index;
    int i = 0;
    
    while (table->status[index] == 1) {  // Пока ячейка занята
        index = (originalIndex + i) % table->size; // Линейное пробирование
        i++;
    }

    table->openTable[index] = (char*)malloc(strlen(word) + 1);
    strcpy(table->openTable[index], word);
    table->status[index] = 1;  // Ячейка теперь занята
}

// Вставка слова с закрытой адресацией (цепочки)
void insertClosed(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->word, word);
    newNode->next = table->table[index];
    table->table[index] = newNode;
}

// Поиск слова с открытой адресацией
char* searchOpen(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    int originalIndex = index;
    int i = 0;

    while (table->status[index] != 0) {
        table->comparisons++;
        if (table->status[index] == 1 && strcmp(table->openTable[index], word) == 0) {
            return table->openTable[index];
        }
        index = (originalIndex + i) % table->size;
        i++;
    }
    return NULL;
}

// Поиск слова с закрытой адресацией
HashNode* searchClosed(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    HashNode* node = table->table[index];
    
    while (node) {
        table->comparisons++;
        if (strcmp(node->word, word) == 0) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

// Удаление слова с открытой адресацией
void deleteOpen(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    int originalIndex = index;
    int i = 0;

    while (table->status[index] != 0) {
        table->comparisons++;
        if (table->status[index] == 1 && strcmp(table->openTable[index], word) == 0) {
            free(table->openTable[index]);
            table->openTable[index] = NULL;
            table->status[index] = 2; // Ячейка теперь помечена как удаленная
            return;
        }
        index = (originalIndex + i) % table->size;
        i++;
    }
}

// Удаление слова с закрытой адресацией
void deleteClosed(HashTable* table, const char* word) {
    unsigned int index = hash(word, table->size);
    HashNode* node = table->table[index];
    HashNode* prev = NULL;

    while (node) {
        table->comparisons++;
        if (strcmp(node->word, word) == 0) {
            if (prev) {
                prev->next = node->next;
            } else {
                table->table[index] = node->next;
            }
            free(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

// Вывод хеш-таблицы для закрытой адресации
void printTableClosed(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        HashNode* node = table->table[i];
        if (node) {
            printf("Index %d: ", i);
            while (node) {
                printf("%s -> ", node->word);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
}

// Вывод хеш-таблицы для открытой адресации
void printTableOpen(HashTable* table) {
    for (int i = 0; i < table->size; i++) {
        if (table->status[i] == 1) {
            printf("Index %d: %s\n", i, table->openTable[i]);
        }
    }
}

// Чтение слов из файла
void readWordsFromFile(const char* filename, HashTable* table) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Не удалось открыть файл.\n");
        return;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        insertClosed(table, word); // Используем закрытую адресацию для вставки
    }

    fclose(file);
}

int main() {
    int size = 10; // Размер хеш-таблицы
    HashTable* tableClosed = createTable(size); // Для закрытой адресации
    HashTable* tableOpen = createTable(size);   // Для открытой адресации

    // Чтение слов из файла
    readWordsFromFile("words.txt", tableClosed);
    readWordsFromFile("words.txt", tableOpen);

    // Выводим хеш-таблицу (закрытая адресация)
    printf("Таблица с закрытой адресацией после добавления слов:\n");
    printTableClosed(tableClosed);

    // Выводим хеш-таблицу (открытая адресация)
    printf("Таблица с открытой адресацией после добавления слов:\n");
    printTableOpen(tableOpen);

    // Поиск и подсчёт сравнений
    const char* wordToSearch = "example"; // Измените на любое слово для поиска
    tableClosed->comparisons = 0;
    HashNode* foundNodeClosed = searchClosed(tableClosed, wordToSearch);
    printf("Поиск с закрытой адресацией для '%s': %d сравнений.\n", wordToSearch, tableClosed->comparisons);

    tableOpen->comparisons = 0;
    char* foundWordOpen = searchOpen(tableOpen, wordToSearch);
    printf("Поиск с открытой адресацией для '%s': %d сравнений.\n", wordToSearch, tableOpen->comparisons);

    // Удаление и подсчёт сравнений
    tableClosed->comparisons = 0;
    deleteClosed(tableClosed, wordToSearch);
    printf("Удаление с закрытой адресацией для '%s': %d сравнений.\n", wordToSearch, tableClosed->comparisons);

    tableOpen->comparisons = 0;
    deleteOpen(tableOpen, wordToSearch);
    printf("Удаление с открытой адресацией для '%s': %d сравнений.\n", wordToSearch, tableOpen->comparisons);

    // Выводим таблицу после удаления (закрытая адресация)
    printf("Таблица с закрытой адресацией после удаления слова '%s':\n", wordToSearch);
    printTableClosed(tableClosed);

    // Выводим таблицу после удаления (открытая адресация)
    printf("Таблица с открытой адресацией после удаления слова '%s':\n", wordToSearch);
    printTableOpen(tableOpen);

    // Освобождение памяти
    for (int i = 0; i < tableClosed->size; i++) {
        HashNode* node = tableClosed->table[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    for (int i = 0; i < tableOpen->size; i++) {
        if (tableOpen->status[i] == 1) {
            free(tableOpen->openTable[i]);
        }
    }

    free(tableClosed->table);
    free(tableClosed->status);
    free(tableClosed->openTable);
    free(tableClosed);
    free(tableOpen->table);
    free(tableOpen->status);
    free(tableOpen->openTable);
    free(tableOpen);

    return 0;
}
