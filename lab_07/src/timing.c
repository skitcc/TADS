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

int compare_time(const char *filename, int size) 
{
    struct tree_interface bst = init_tree_as_bst();
    struct tree_interface avl = init_tree_as_avl();

    PRINT_COLOR(VIOLET, "Введите символ для удаления");
    char target = 0;
    char buffer[100];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL || sscanf(buffer, "%c", &target) != 1) {
        PRINT_COLOR(RED, "Ошибка чтения символа для удаления!\n");
        return 1;
    }

    uint64_t avg_bst = 0;
    int comp_bst = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        bst.root = bst.init(filename);
        if (bst.root == NULL) 
        {
            PRINT_COLOR(RED, "Ошибка построения дерева!\n");
            return 1;
        }
        int comparisons = 0;
        uint64_t start_tick = tick_count();
        bst.root = bst.delete(bst.root, target, &comparisons);
        uint64_t end_tick = tick_count();
        avg_bst += (end_tick - start_tick);
        comp_bst += comparisons;
        bst.destroy(bst.root);
    }
    avg_bst /= MAX_MEASURMENTS;
    comp_bst /= MAX_MEASURMENTS;

    uint64_t avg_avl = 0;
    int comp_avl = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        bst.root = bst.init(filename);
        avl.root = avl.balance(bst.root);
        int comparisons = 0;
        uint64_t start_tick = tick_count();
        avl.root = avl.delete(avl.root, target, &comparisons);
        uint64_t end_tick = tick_count();
        comp_avl += comparisons;
        avg_avl += (end_tick - start_tick);
        avl.destroy(avl.root);
    }
    avg_avl /= MAX_MEASURMENTS;
    comp_avl /= MAX_MEASURMENTS;

    PRINT_COLOR(VIOLET, "Введите слово для удаления в хэш таблицах");
    char word[100];
    if (fgets(word, sizeof(word), stdin) == NULL)
    {
        PRINT_COLOR(RED, "Ошибка чтения слова!");
        return 1;
    }
    word[strlen(word) - 1] = '\0';
    open_ht *open_table = NULL;
    closed_ht *closed_table = NULL;
    uint64_t avg_open_ht = 0;
    uint64_t avg_closed_ht = 0;
    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        open_table = create_open_table(size);
        closed_table = create_closed_table(size);
        read_file_to_hts(filename, closed_table, open_table);
        uint64_t start_tick = tick_count();
        delete_open(open_table, word);
        uint64_t end_tick = tick_count();


        avg_open_ht += (end_tick - start_tick);
        start_tick = tick_count();
        delete_closed(closed_table, word);
        end_tick = tick_count();

        avg_closed_ht += (end_tick - start_tick);
        free_closed_table(closed_table);
        free_open_table(open_table);
    }
    avg_open_ht /= MAX_MEASURMENTS;
    avg_closed_ht /= MAX_MEASURMENTS;

    PRINT_COLOR(VIOLET, "Введите слово для поиска в хэш таблицах и деревьях");
    if (fgets(word, sizeof(word), stdin) == NULL)
    {
        PRINT_COLOR(RED, "Ошибка чтения слова!");
        return 1;
    }
    word[strlen(word) - 1] = '\0';

    
    uint64_t avg_bst_search = 0;
    int comp_bst_search = 0;

    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        bst.root = bst.init(filename);
        if (!bst.root) 
        {
            PRINT_COLOR(RED, "Ошибка построения BST!\n");
            return 1;
        }

        int comparisons = 0;
        uint64_t start_tick = tick_count();
        bst.search(bst.root, word, &comparisons);
        uint64_t end_tick = tick_count();

        avg_bst_search += (end_tick - start_tick);
        comp_bst_search += comparisons;

        bst.destroy(bst.root);
    }
    avg_bst_search /= MAX_MEASURMENTS;
    comp_bst_search /= MAX_MEASURMENTS;

    uint64_t avg_avl_search = 0;
    int comp_avl_search = 0;

    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        bst.root = bst.init(filename);
        avl.root = avl.balance(bst.root);
        if (!avl.root) 
        {
            PRINT_COLOR(RED, "Ошибка построения AVL!\n");
            return 1;
        }

        int comparisons = 0;
        uint64_t start_tick = tick_count();
        avl.search(avl.root, word, &comparisons);
        uint64_t end_tick = tick_count();

        avg_avl_search += (end_tick - start_tick);
        comp_avl_search += comparisons;

        bst.destroy(bst.root);
        avl.destroy(avl.root);
    }
    avg_avl_search /= MAX_MEASURMENTS;
    comp_avl_search /= MAX_MEASURMENTS;

    uint64_t avg_open_ht_search = 0;
    int comp_open_ht_search = 0;

    uint64_t avg_closed_ht_search = 0;
    int comp_closed_ht_search = 0;

    for (int i = 0; i < MAX_MEASURMENTS; i++) 
    {
        open_ht *open_table = create_open_table(size);
        closed_ht *closed_table = create_closed_table(size);
        read_file_to_hts(filename, closed_table, open_table);

        int comparisons_open = 0;
        uint64_t start_tick = tick_count();
        search_open(open_table, word);
        uint64_t end_tick = tick_count();

        avg_open_ht_search += (end_tick - start_tick);
        comp_open_ht_search += comparisons_open;

        // Поиск в таблице с закрытой адресацией
        int comparisons_closed = 0;
        start_tick = tick_count();
        search_closed(closed_table, word);
        end_tick = tick_count();

        avg_closed_ht_search += (end_tick - start_tick);
        comp_closed_ht_search += comparisons_closed;

        free_closed_table(closed_table);
        free_open_table(open_table);
    }
    avg_open_ht_search /= MAX_MEASURMENTS;
    comp_open_ht_search /= MAX_MEASURMENTS;

    avg_closed_ht_search /= MAX_MEASURMENTS;
    comp_closed_ht_search /= MAX_MEASURMENTS;

    open_table = create_open_table(1000);
    closed_table = create_closed_table(1000);
    read_file_to_hts(filename, closed_table, open_table);
    search_open(open_table, word);
    search_closed(closed_table, word);

    comp_open_ht_search = open_table->comparisons;
    comp_closed_ht_search = closed_table->comparisons;

    free_closed_table(closed_table);
    free_open_table(open_table);



    printf("Удаление для BST: %" PRIu64 " тактов\n", avg_bst);
    printf("Удаление для AVL: %" PRIu64 " тактов\n", avg_avl);

    printf("Кол-во сравнений для BST для удаления %d\n", comp_bst);
    printf("Кол-во сравнений для AVL для удаления %d\n", comp_avl - (comp_avl % 10));


    printf("Удаление слова в хэш таблице с открытой адресацией: %" PRIu64 " тактов\n", avg_open_ht);
    printf("Удаление слова в хэш таблице с закрытой адресацией: %" PRIu64 " тактов\n", avg_closed_ht);

    printf("Поиск в BST: %" PRIu64 " тактов, сравнений: %d\n", avg_bst_search, comp_bst_search);
    printf("Поиск в AVL: %" PRIu64 " тактов, сравнений: %d\n", avg_avl_search, comp_avl_search);

    printf("Поиск в хэш-таблице с открытой адресацией: %" PRIu64 " тактов, сравнений: %d\n", avg_open_ht_search, comp_open_ht_search);
    printf("Поиск в хэш-таблице с закрытой адресацией: %" PRIu64 " тактов, сравнений: %d\n", avg_closed_ht_search, comp_closed_ht_search);


    return 0;
}

