#include "timing.h"

uint64_t tick_count(void) 
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
    );

    uint64_t ticks = ((uint64_t)high << 32) | low;
    return ticks;
}

int compare_time(const char *filename) 
{
    node_t *root = NULL;

    PRINT_COLOR(VIOLET, "Введите символ для удаления");
    char target = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%c", &target) != 1) {
        PRINT_COLOR(RED, "Ошибка чтения символа для удаления!\n");
        return 1;
    }

    uint64_t avg_tree = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        root = build_tree_from_file(filename);
        if (root == NULL) 
        {
            PRINT_COLOR(RED, "Ошибка построения дерева!\n");
            return 1;
        }

        uint64_t start_tick = tick_count();
        root = delete_nodes_starting_with(root, target);
        uint64_t end_tick = tick_count();
        avg_tree += (end_tick - start_tick);

        free_tree(root);
    }
    avg_tree /= MAX_MEASURMENTS;

    uint64_t avg_file = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        uint64_t start_tick = tick_count();
        int new_size = delete_elems_starts_with(filename, target);
        uint64_t end_tick = tick_count();
        if (new_size == -1)
            return 1;
        avg_file += (end_tick - start_tick);
    }
    avg_file /= MAX_MEASURMENTS;

    printf("Удаление для дерева: %" PRIu64 " тактов\n", avg_tree);
    printf("Удаление для файла: %" PRIu64 " тактов\n", avg_file);

    PRINT_COLOR(VIOLET, "Введите элемент для поиска");
    char value[100];
    if (fgets(value, sizeof(value), stdin) == NULL) 
    {
        PRINT_COLOR(RED, "Ошибка чтения элемента для поиска!\n");
        return 1;
    }
    value[strcspn(value, "\n")] = '\0';

    uint64_t tree_search_avg = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        root = build_tree_from_file(filename);
        if (root == NULL) 
        {
            PRINT_COLOR(RED, "Ошибка построения дерева!\n");
            return -1;
        }

        uint64_t start_tick = tick_count();
        search_node(root, value);
        uint64_t end_tick = tick_count();
        tree_search_avg += (end_tick - start_tick);

        free_tree(root);
    }
    tree_search_avg /= MAX_MEASURMENTS;

    uint64_t file_search_avg = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        uint64_t start_tick = tick_count();
        int found = search_in_file(filename, value);
        uint64_t end_tick = tick_count();
        if (found == -1)
            return 1;
        file_search_avg += (end_tick - start_tick);
    }
    file_search_avg /= MAX_MEASURMENTS;

    printf("Поиск для дерева: %" PRIu64 " тактов\n", tree_search_avg);
    printf("Поиск для файла: %" PRIu64 " тактов\n", file_search_avg);
    return 0;
}

