#include "utils.h"


// Инициализация статического стека
void init_static_array_stack(static_array_stack_t *s) 
{
    s->top = -1;
}

// Инициализация динамического стека
void init_dynamic_array_stack(dynamic_array_stack_t *s) 
{
    s->top = -1;
    s->capacity = INITIAL_CAPACITY;
    s->data = (char *)malloc((size_t)s->capacity * sizeof(char));
    if (s->data == NULL) {
        printf("%sОшибка выделения памяти для динамического стека.%s\n", RED, RESET);
    }
}

// Инициализация стека-списка
list_stack_t *init_list_stack() 
{
    return NULL;
}

size_t calculate_list_memory(const list_stack_t *stack) 
{
    size_t size = 0;
    const list_stack_t *current = stack;
    while (current != NULL) {
        size += sizeof(list_stack_t); // Память под каждый узел
        current = current->next;
    }
    return size;
}