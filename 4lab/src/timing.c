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

    int open_count = size / 2;  
    int close_count = size / 2; 
    int index = 0;             

    // Генерируем строку
    for (int i = 0; i < size; i++) {
        if (open_count > 0) { 
            result[index++] = '(';
            open_count--;
        } else {
            result[index++] = ')'; 
            close_count--;
        }

        if (open_count == 0 && close_count > 0) {
            while (close_count > 0) {
                result[index++] = ')';
                close_count--;
            }
        }
    }
    
    result[size] = '\0'; // Нуль-терминатор для строки
    return result; // Возвращаем результат
}

void compare_time(int size)
{
    static_array_stack_t st_stack;
    dynamic_array_stack_t dn_stack;
    list_stack_t *li_stack = NULL;

    initialize_stacks(&st_stack, &dn_stack, &li_stack);

    uint64_t avg_st = 0, avg_dn = 0, avg_li = 0;
    const char *expr = generate_balanced_parentheses(size);
    fill_stack_from_expression(expr, &st_stack, STATIC_ARRAY);
    
    fill_stack_from_expression(expr, &dn_stack, DYNAMIC_ARRAY);
    printf("1\n");
    fill_list(expr, &li_stack);
    for (int i = 0; i < 100; i++)
    {
        uint64_t start_tick = tick_count();
        check_brackets((void *)&st_stack, STATIC_ARRAY);
        uint64_t end_tick = tick_count();
        avg_st += (end_tick - start_tick);
    }
    avg_st /= 100;

    printf("Время выполнения проверки правильности расстановки скобок для стека на статическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_st);

    for (int i = 0; i < 100; i++)
    {
        uint64_t start_tick = tick_count();
        check_brackets((void *)&dn_stack, DYNAMIC_ARRAY);
        uint64_t end_tick = tick_count();
        avg_dn += (end_tick - start_tick);
    }
    avg_dn /= 100;

    printf("Время выполнения проверки правильности расстановки скобок для стека на динамическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_dn);

    for (int i = 0; i < 100; i++)
    {
        uint64_t start_tick = tick_count();
        check_brackets_list(li_stack);
        uint64_t end_tick = tick_count();
        avg_li += (end_tick - start_tick);
    }
    avg_li /= 100;

    printf("Время выполнения проверки правильности расстановки скобок для стека на списке(размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_st);

 

}