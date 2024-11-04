#include "stack_operations.h"



void free_dynamic_array_stack(dynamic_array_stack_t *stack) 
{
    if (stack == NULL)
        return;
    if (stack->data != NULL) {
        free(stack->data); 
        stack->data = NULL; 
    }
    stack->top = -1;  // Сбрасываем указатель на вершину стека
}

void free_list_stack(list_stack_t **stack) 
{
    list_stack_t *current = *stack;
    list_stack_t *next_node;

    while (current != NULL) {
        next_node = current->next; 
        free(current);  // Освобождаем текущий узел
        current = next_node;  // Переходим к следующему узлу
    }

    *stack = NULL;  // Обнуляем указатель на стек, чтобы он не указывал на освобожденную память
}


// Проверка на пустоту (общая функция)
bool is_empty(void *stack, stack_type_t type) 
{
    if (type == STATIC_ARRAY) 
        return ((static_array_stack_t *)stack)->top == -1;
    else if (type == DYNAMIC_ARRAY) 
        return ((dynamic_array_stack_t *)stack)->top == -1;
    else if (type == LIST) 
        return stack == NULL;
    
    return true;
}


void push_st(static_array_stack_t *stack, char value)
{
    if (stack->top < MAX_LEN_STACK - 1) 
        stack->data[++(stack->top)] = value;
}

void push_dn(dynamic_array_stack_t *stack, char value) 
{
    // printf("top : %d\n", stack->top);
    if (stack->top >= stack->capacity - 1) {
        // Увеличиваем емкость в два раза
        // printf("current_capacity : %d\n", stack->capacity);
        stack->capacity *= 2;
        char *new_data = (char *)realloc(stack->data, (size_t)stack->capacity * sizeof(char));
        if (new_data == NULL) {
            printf("%sОшибка выделения дополнительной памяти для динамического стека.%s\n", RED, RESET);
            return; // Ошибка, не добавляем элемент
        }
        stack->data = new_data;
    }

    // Добавляем элемент в стек
    stack->data[++(stack->top)] = value;
}


int push_list(list_stack_t **stack, char value)
{
    list_stack_t *newNode = (list_stack_t *)malloc(sizeof(list_stack_t));
    if (newNode == NULL) 
    {
        printf("%sОшибка выделения памяти для элемента списка.%s\n", RED, RESET);
        return ERR_ALLOCATION;
    }
    newNode->data = value;
    newNode->next = (list_stack_t *)(*stack); 
    *stack = newNode;
    return EXIT_SUCCESS;
}


char pop_st(static_array_stack_t *stack, removed_addresses_tracker_t *tracker)
{
    if (tracker != NULL) 
        tracker->removed_addresses[tracker->count++] = (char *)&stack->data[(stack->top)];
    if (stack->top >= 0)
    {
        return stack->data[(stack->top)--];
    } 
    return '\0';
}

char pop_dn(dynamic_array_stack_t *stack, removed_addresses_tracker_t *tracker)
{
    if (tracker != NULL) 
        tracker->removed_addresses[tracker->count++] = (char *)&stack->data[(stack->top)];
    if (stack->top >= 0) 
        return stack->data[(stack->top)--];
    return '\0';
}


char pop_list(list_stack_t **stack, removed_addresses_tracker_t *tracker)
{
    list_stack_t *top = *stack;
    char value = top->data;
    if (tracker != NULL) 
        tracker->removed_addresses[tracker->count++] = (char *)&top->data;
    *stack = top->next;
    free(top);
    return value;
}
// Вывод текущего состояния стека
void print_stack(void *stack, stack_type_t type) 
{
    if (type == STATIC_ARRAY) 
    {
        static_array_stack_t *s = (static_array_stack_t *)stack;
        printf("Стек (статический массив): ");
        for (int i = s->top; i >= 0; i--) 
            printf("%c ", s->data[i]);
        printf("\n");
    } 
    else if (type == DYNAMIC_ARRAY) 
    {
        dynamic_array_stack_t *s = (dynamic_array_stack_t *)stack;
        printf("Стек (динамический массив): ");
        for (int i = s->top; i >= 0; i--) 
            printf("%c ", s->data[i]);
        printf("\n");
    } 
    else if (type == LIST) 
    {
        list_stack_t *current = (list_stack_t *)stack;
        printf("Стек (список): ");
        while (current != NULL) 
        {
            printf("%c ", current->data);
            current = current->next;
        }
        printf("\n");
    }
}

// Проверка правильности расстановки скобок
bool check_brackets_st(static_array_stack_t *stack, stack_type_t type, const char *expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        char current = expr[i];
        // Если это открывающая скобка, добавляем её в стек
        if (current == '(' || current == '{' || current == '[') {
            push_st(stack, current);
        }
        // Если это закрывающая скобка, проверяем соответствие
        else if (current == ')' || current == '}' || current == ']') {
            if (is_empty(stack, type)) {
                // Стек пуст, но встретилась закрывающая скобка — ошибка
                return false;
            }
            char top = pop_st(stack, NULL);
            if ((current == ')' && top != '(') ||
                (current == ']' && top != '[') ||
                (current == '}' && top != '{')) {
                // Несоответствие пар скобок — ошибка
                return false;
            }
        }
    }

    // Проверка на остатки в стеке (лишние открывающие скобки)
    return is_empty(stack, type);
}


bool check_brackets_dn(dynamic_array_stack_t *stack, stack_type_t type, const char *expr) {
    for (int i = 0; expr[i] != '\0'; i++) {
        char current = expr[i];
        // Если это открывающая скобка, добавляем её в стек
        if (current == '(' || current == '{' || current == '[') {
            push_dn(stack, current);
        }
        // Если это закрывающая скобка, проверяем соответствие
        else if (current == ')' || current == '}' || current == ']') {
            if (is_empty(stack, type)) {
                // Стек пуст, но встретилась закрывающая скобка — ошибка
                return false;
            }
            char top = pop_dn(stack, NULL);
            if ((current == ')' && top != '(') ||
                (current == ']' && top != '[') ||
                (current == '}' && top != '{')) {
                // Несоответствие пар скобок — ошибка
                return false;
            }
        }
    }

    // Проверка на остатки в стеке (лишние открывающие скобки)
    return is_empty(stack, type);
}


bool check_brackets_list(list_stack_t **stack, const char *expr) 
{
    // Проходим по каждому символу в выражении
    for (int i = 0; expr[i] != '\0'; i++) {
        char current = expr[i];

        // Если это открывающая скобка, добавляем её в стек
        if (current == '(' || current == '{' || current == '[') {
            if (push_list(stack, current) != EXIT_SUCCESS) {
                return false;
            }
        }
        // Если это закрывающая скобка, проверяем соответствие
        else if (current == ')' || current == '}' || current == ']') {
            if (*stack == NULL) {
                return false;
            }
            char top = pop_list(stack, NULL);
            if ((current == ')' && top != '(') ||
                (current == ']' && top != '[') ||
                (current == '}' && top != '{')) {
                return false;
            }
        }
    }

    bool result = (*stack == NULL);
    free_list_stack(stack);
    return result;
}
