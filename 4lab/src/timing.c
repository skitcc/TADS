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

    initialize_stacks(&st_stack, &dn_stack, &li_stack);


    uint64_t avg_st = 0, avg_dn = 0, avg_li = 0;
    const char *expr = generate_balanced_parentheses(size);
    printf("%s\n", expr);
    
    
    
    for (int i = 0; i < 100; i++)
    {
        fill_stack_from_expression(expr, &st_stack, STATIC_ARRAY);
        uint64_t start_tick = tick_count();
        check_brackets((void *)&st_stack, STATIC_ARRAY);
        uint64_t end_tick = tick_count();
        avg_st += (end_tick - start_tick);
        init_static_array_stack(&st_stack);
        
    }
    avg_st /= 100;

    printf("Время выполнения проверки правильности расстановки скобок для стека на статическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_st);
    

    for (int i = 0; i < 100; i++)
    {
        // Заполнение стека выражением
        fill_stack_from_expression(expr, &dn_stack, DYNAMIC_ARRAY);

        // Измерение времени выполнения функции
        uint64_t start_tick = tick_count();
        check_brackets((void *)&dn_stack, DYNAMIC_ARRAY);
        uint64_t end_tick = tick_count();
        avg_dn += (end_tick - start_tick);
        free_dynamic_array_stack(&dn_stack);
        init_dynamic_array_stack(&dn_stack);
    }

    avg_dn /= 100;
    // init_dynamic_array_stack(&dn_stack);
    // fill_stack_from_expression(expr, &dn_stack, DYNAMIC_ARRAY);
    // uint64_t start_tick = tick_count();
    // check_brackets((void *)&dn_stack, DYNAMIC_ARRAY);
    // uint64_t end_tick = tick_count();
    // avg_dn += (end_tick - start_tick);
    // avg_dn /= 100;
    printf("Время выполнения проверки правильности расстановки скобок для стека на динамическом массиве (размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_dn);

    for (int i = 0; i < 100; i++) {
        fill_list(expr, &li_stack);
        if (li_stack == NULL) {
            printf("Ошибка: стек пустой перед вызовом функции.\n");
            break;
        };
        uint64_t start_tick = tick_count();
        check_brackets_list(li_stack);
        uint64_t end_tick = tick_count();
        avg_li += (end_tick - start_tick);

        li_stack = init_list_stack();
        
    }
    // li_stack = init_list_stack();
    // fill_list(expr, &li_stack);
    // uint64_t start_tick = tick_count();
    // check_brackets_list(li_stack);
    // uint64_t end_tick = tick_count();
    // avg_li += (end_tick - start_tick);

    // free_list_stack(&li_stack);
    avg_li /= 100;

    printf("Время выполнения проверки правильности расстановки скобок для стека на списке(размер : %d):\n", size);
    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, avg_li);

 

}