#include "sort.h"

void swap(void *a, void *b, size_t size)
{
    char temp[256]; 
    if (size <= sizeof(temp)) 
    {
        memcpy(temp, a, size);
        memcpy(a, b, size);
        memcpy(b, temp, size);
    }
}

int bubble_sort_generic(void *array, int n, size_t size, int (*cmp)(const void *, const void *))
{

    if (n == 0)
    {
        printf("Ошибка пустой файл!\n");
        return 2;
    }
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            void *a = (char*)array + j * size;
            void *b = (char*)array + (j + 1) * size;

            if (cmp(a, b) > 0) 
                swap(a, b, size); 
        }
    }
    return 0;
}

int compare_structs(const void *a, const void *b)
{
    desc_t *x = (desc_t *)a;
    desc_t *y = (desc_t *)b;
    return (x->rooms_quantity - y->rooms_quantity);
}

int compare_keys(const void *a, const void *b)
{
    keys_t *x = (keys_t *)a;
    keys_t *y = (keys_t *)b;
    return (x->rooms_quantity - y->rooms_quantity);
}

int bubble_sort_structs(desc_t *array, int n)
{
    return bubble_sort_generic(array, n, sizeof(desc_t), compare_structs);
}

int bubble_sort_keys(keys_t *keys, int n)
{
    return bubble_sort_generic(keys, n, sizeof(keys_t), compare_keys);
}

int qsort_generic(void *array, int n, size_t size, int (*cmp)(const void *, const void *))
{
    if (n == 0)
    {
        printf("Ошибка пустой файл!\n");
        return 2;
    }
    qsort(array, n, size, cmp);
    return EXIT_SUCCESS;
}


int qsort_structs(desc_t *array, int n)
{
    return qsort_generic(array, n, sizeof(desc_t), compare_structs);
}

int qsort_keys(keys_t *keys, int n)
{
    return qsort_generic(keys, n, sizeof(keys_t), compare_keys);
}