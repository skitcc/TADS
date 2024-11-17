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

    printf("Введите символ для удаления\n");
    char target;
    char buffer[100];
    // while(getchar() != '\n');
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%c", &target) != 1)
    {
        return 1;
    }
    printf("1\n");

    uint64_t avg_tree = 0;
    for (int i = 0; i < 1000; i++)
    {
        root = build_tree_from_file(filename);
        if (root == NULL)
            return 1;
        uint64_t start_tick = tick_count();
        root = delete_nodes_starting_with(root, target);
        uint64_t end_tick = tick_count();
        avg_tree += (end_tick - start_tick);
        free_tree(root);
    }
    avg_tree /= 1000;

    uint64_t avg_mas = 0;
    char **mas = NULL;

    for (int i = 0; i < 1000; i++)
    {
        int len = 0;
        mas = build_mas_from_file(filename, &len);
        uint64_t start_tick = tick_count();
        int new_size = delete_elems_starts_with(mas, len, target);
        uint64_t end_tick = tick_count();
        avg_mas += (end_tick - start_tick);
        free_mas(mas, new_size);
    }
    avg_mas /= 1000;


    printf("Удаление для дерева Такты: %" PRIu64 "\n", avg_tree);
    printf("Удаление для массива Такты: %" PRIu64 "\n", avg_mas);

    return 0;
}

