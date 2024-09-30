#include "time_calc.h"

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

void print_result(int64_t start, int64_t end)
{
    printf("%10ld тактов | %15.10lf секунд |\n", end - start, (double)(end - start)/GHZ);
}

int compare_sorts()
{
    int64_t start1, end1, start2, end2, start4, end4;
    
    desc_t array[MAX_SIZE_ARRAY];
    desc_t array_copy[MAX_SIZE_ARRAY];
    keys_t keys[MAX_SIZE_ARRAY];
    keys_t keys_copy[MAX_SIZE_ARRAY];

    int n = 0;  
    int rc = load_data(array, &n, keys);  
    if (rc != 0)
        return rc;
    
    for (int i = 0; i < n; i++)
        array_copy[i] = array[i];

    printf("\n\nСортировка файла из %d записей\n\n", n);
    puts("|----------------------------------------------------------------------------------|");

    start1 = tick_count();
    bubble_sort_structs(array, n);  
    end1 = tick_count();

    printf("| Сортировка таблицы пузырьком         |");
    print_result(start1, end1);
    puts("|----------------------------------------------------------------------------------|");
 
    start2 = tick_count();
    bubble_sort_keys(keys, n);  
    end2 = tick_count();

    printf("| Сортировка таблицы ключей пузырьком  |");
    print_result(start2, end2);
    puts("|----------------------------------------------------------------------------------|");

    for (int i = 0; i < n; i++)
    {
        array[i] = array_copy[i];
        keys[i] = keys_copy[i];
    }

    start2 = tick_count();
    qsort_structs(array, n);  
    end2 = tick_count();

    printf("| Сортировка таблицы qsort             |");
    print_result(start2, end2);
    puts("|----------------------------------------------------------------------------------|");   
        
    start4 = tick_count();
    qsort_keys(keys, n);  
    end4 = tick_count();

    printf("| Сортировка таблицы ключей qsort      |");
    print_result(start4, end4);
    puts("|----------------------------------------------------------------------------------|"); 
    
    printf("\n%lu размер таблицы (в байтах)\n\n", sizeof(*array) * n);
    printf("\n%lu размер таблицы ключей (в байтах)\n\n", sizeof(*keys) * n);
    
    return rc;
}