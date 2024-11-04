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

char* generate_balanced_parentheses(int size) {
    if (size % 2 != 0) {
        return NULL; 
    }

    char* result = (char*)malloc(size + 1); 
    if (result == NULL) {
        return NULL; 
    }

    // Генерируем строку
    for (int i = 0; i < size; i++) {
        if (i % 2 == 0)
        {
            result[i] = '(';
        }
        else
            result[i] = ')';
    }
    
    result[size] = '\0'; // Нуль-терминатор для строки
    return result; // Возвращаем результат
}

void compare_time(int size)
{
    static_array_stack_t st_stack;
    dynamic_array_stack_t dn_stack;
    list_stack_t *li_stack = NULL;

    uint64_t avg_st = 0, avg_dn = 0, avg_li = 0;
    const char *expr = generate_balanced_parentheses(size);
    printf("%s\n", expr);
    
    for (int i = 0; i < 1000; i++)
    {
        init_static_array_stack(&st_stack);
        uint64_t start_tick = tick_count();
        check_brackets_st(&st_stack, STATIC_ARRAY, expr);
        uint64_t end_tick = tick_count();
        avg_st += (end_tick - start_tick);
    }
    avg_st /= 1000;

    printf("Время выполнения проверки правильности расстановки скобок для стека на статическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_st);
    

    for (int i = 0; i < 1000; i++)
    {
        // Измерение времени выполнения функции
        init_dynamic_array_stack(&dn_stack, size);
        uint64_t start_tick = tick_count();
        check_brackets_dn(&dn_stack, DYNAMIC_ARRAY, expr);
        uint64_t end_tick = tick_count();
        avg_dn += (end_tick - start_tick);
        free_dynamic_array_stack(&dn_stack);
    }

    avg_dn /= 1000;
    printf("Время выполнения проверки правильности расстановки скобок для стека на динамическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_dn);
    // printf("Средняя память, используемая списком: %zu байт\n", sizeof);
    // int total_list_memory = 0;
    for (int i = 0; i < 1000; i++) {
        li_stack = init_list_stack();
        uint64_t start_tick = tick_count();
        check_brackets_list(&li_stack,expr);
        uint64_t end_tick = tick_count();
        avg_li += (end_tick - start_tick);
        // int total_list_memory = calculate_list_memory(li_stack);
    }
    avg_li /= 1000;
    
    printf("Время выполнения проверки правильности расстановки скобок для стека на списке(размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_li);
    // printf("Средняя память, используемая списком: %zu байт\n", total_list_memory);
    // free(expr);
 

}