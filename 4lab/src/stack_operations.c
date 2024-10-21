#include "stack_operations.h"


// Инициализация статического стека
void init_static_array_stack(static_array_stack_t *s) 
{
    s->top = -1;
}

// Инициализация динамического стека
void init_dynamic_array_stack(dynamic_array_stack_t *s) 
{
    s->top = -1;
    s->capacity = 10;
    s->data = (char *)malloc(s->capacity * sizeof(char));
    if (s->data == NULL) {
        printf("%sОшибка выделения памяти для динамического стека.%s\n", RED, RESET);

    }
}

// Инициализация стека-списка
list_stack_t *init_list_stack() 
{
    return NULL;
}

void free_dynamic_array_stack(dynamic_array_stack_t *stack) 
{
    if (stack == NULL)
        return;
    if (stack->data != NULL) {
        free(stack->data);  // Освобождаем память, выделенную для динамического массива
        stack->data = NULL;  // Обнуляем указатель для предотвращения повторного освобождения
    }
    stack->top = -1;  // Сбрасываем указатель на вершину стека
    stack->capacity = 0;  // Обнуляем ёмкость стека
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

// Push элемент в стек
int push(void *stack, stack_type_t type, char value) 
{
    if (type == STATIC_ARRAY) 
    {
        static_array_stack_t *s = (static_array_stack_t *)stack;
        if (s->top < MAX_LEN_STACK - 1) 
            s->data[++(s->top)] = value;
        else 
        {
            printf("%sСтек (статический массив) полон.%s\n", RED, RESET);
            return STACK_OVERFLOW;
        }
        
    } 
    else if (type == DYNAMIC_ARRAY) 
    {
        dynamic_array_stack_t *s = (dynamic_array_stack_t *)stack;
        if (s->top == s->capacity - 1) 
        {
            s->capacity *= 2;
            s->data = (char *)realloc(s->data, s->capacity * sizeof(char));
            if (s->data == NULL) 
            {
                printf("%sОшибка выделения памяти при расширении динамического стека.%s\n", RED, RESET);
                return ERR_ALLOCATION;
            }
        }
        s->data[++(s->top)] = value;
    } 
    else if (type == LIST) 
    {
        list_stack_t *newNode = (list_stack_t *)malloc(sizeof(list_stack_t));
        if (newNode == NULL) 
        {
            printf("%sОшибка выделения памяти для элемента списка.%s\n", RED, RESET);
            return ERR_ALLOCATION;
        }
        newNode->data = value;
        newNode->next = (list_stack_t *)stack;
        stack = newNode;
    }
    return EXIT_SUCCESS;
}

// Pop элемент из стека
char pop(void *stack, stack_type_t type) 
{
    if (type == STATIC_ARRAY) 
    {
        static_array_stack_t *s = (static_array_stack_t *)stack;
        if (s->top >= 0) 
            return s->data[(s->top)--];
    } 
    else if (type == DYNAMIC_ARRAY) 
    {
        dynamic_array_stack_t *s = (dynamic_array_stack_t *)stack;
        if (s->top >= 0) 
            return s->data[(s->top)--];
    }
    else if (type == LIST) 
    {
        if (stack != NULL) 
        {
            list_stack_t *top = (list_stack_t *)stack;
            char value = top->data;
            stack = top->next;
            free(top);
            return value;
        }
    }
    return '\0';
}

// Вывод текущего состояния стека
void print_stack(void *stack, stack_type_t type) 
{
    if (type == STATIC_ARRAY) 
    {
        static_array_stack_t *s = (static_array_stack_t *)stack;
        printf("Стек (статический массив): ");
        for (int i = 0; i <= s->top; i++) 
            printf("%c ", s->data[i]);
        printf("\n");
    } 
    else if (type == DYNAMIC_ARRAY) 
    {
        dynamic_array_stack_t *s = (dynamic_array_stack_t *)stack;
        printf("Стек (динамический массив): ");
        for (int i = 0; i <= s->top; i++) 
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
bool check_brackets(const char *expr, void *stack, stack_type_t type) 
{
    for (int i = 0; expr[i] != '\0'; i++) {
        char current = expr[i];

        if (current == '(' || current == '[' || current == '{') 
            push(stack, type, current);
        else if (current == ')' || current == ']' || current == '}')
        {
            if (is_empty(stack, type)) 
            return false;

            char top = pop(stack, type);
            printf("current : %c, top : %c\n", current, top);
            if ((current == ')' && top != '(') ||
                (current == ']' && top != '[') ||
                (current == '}' && top != '{')) {
                return false;
            
        }
    }
    }

    return is_empty(stack, type);
}