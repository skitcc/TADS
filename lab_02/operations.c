#include "operations.h"


int load_data(desc_t *arr, int *n, keys_t *keys)
{
    char filename[MAX_LEN_FILENAME + 1];
    getchar();
    printf("Введите название файла\n");
    if (fgets(filename, MAX_LEN_FILENAME + 1, stdin) == NULL)
    {
        printf("Ошибка чтения названия файла\n");
        return ERROR_READING_FILENAME;
    }
    filename[strlen(filename) - 1] = '\0';
    FILE *f_in = fopen(filename, "r");

    if (f_in == NULL)
    {
        printf("Ошибка в открытии файла\n");
        return ERROR_OPENING_FILE;
    }

    if (!fscanf(f_in, "%d", n))
    {
        printf("Ошибка чтения кол-ва структур\n");
        return ERROR_READING_AMOUNT_OF_STRUCTS;
    }
    if (*n < 1 || *n > MAX_LEN_STRUCTURES)
    {
        printf("Некорретное кол-во структур в файле\n");
        return ERROR_INCORRECT_AMOUNT_SCRUCTS;
    }
    keys[0].index = 0;
    for (int i = 0; i < *n; i++)
    {
        if (read_one_record(&arr[i], f_in, 0))
            return 5;
        keys[i].rooms_quantity = arr[i].rooms_quantity;
        keys[i].index = i;
    }
    printf("%sТаблица из файла успешно считана!%s\n", GREEN, RESET);
    return EXIT_SUCCESS;
    
}

int add_data(desc_t *arr, int *n, keys_t *keys)
{
    if (*n > MAX_LEN_STRUCTURES - 1)
        return ERROR_EXCESS_STRUCTS;


    if (read_one_record(&arr[*n], stdin, 1))
        return ERROR_READING_STRUCT;
    keys[*n].index = *n;
    keys[*n].rooms_quantity = arr[*n].rooms_quantity;

    (*n)++; 
    printf("%sЗапись успешно добавлена в таблицу!%s\n", GREEN, RESET);
    return EXIT_SUCCESS;    
}



int delete_data(desc_t *arr, int *n, keys_t *keys)
{
    printf("\nВведите адрес жилья, которую нужно удалить\n");
    char user_address[MAX_LEN_ADDRESS + 1];
    getchar();
    if (fgets(user_address, MAX_LEN_ADDRESS + 1, stdin) == NULL)
        return ERROR_READING_ADDRESS;

    user_address[strlen(user_address) - 1] = '\0';
    int temp = *n;

    for (int i = 0; i < *n; i++)
    {
        if (strcmp(arr[i].address, user_address))
            continue;

        for (int j = i; j < *n; j++)
        {
            arr[j] = arr[j + 1];
            keys[j] = keys[j + 1];
        }
        i--;
        (*n)--;
    }

    if (*n == temp)
    {
        printf("Введен адрес, несуществующий ни в одной структуре!\n");
        return 0;
    }
    printf("%sЗапись успешно удалена из таблицы!%s\n", GREEN, RESET);
    return 0;
}

