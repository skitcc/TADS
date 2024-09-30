#include "show_info.h"


void show_options(void)
{
    printf("\n1 - Загрузить таблицу из файла\n");
    printf("2 - Вывести текущую таблицу на экран\n");
    printf("3 - Добавить запись в конец таблицы\n");
    printf("4 - Удалить запись по кол-ву комнат\n");
    printf("5 - Вывод вторичного двухкомнатного жилья в указанном ценовом диапазоне без животных\n");
    printf("6 - Отсортировать таблицу по кол-ву комнат по возрастнию пузырьковой сортировкой\n");
    printf("7 - Отсортировать таблицу по кол-ву комнат по возрастанию qsort`ом\n");
    printf("8 - Просмотр отсортированной таблицы ключей при несортированной исходной таблице\n");
    printf("9 - Вывод исходной таблицы в упорядоченном виде, используя упорядоченную таблицу ключей\n");
    printf("10 - вывод результатов сравнения эффективности работы программы при обработке данных в исходной таблице и в таблице ключей\n");

}

int print_task_version(desc_t *arr, int n)
{
    float start = 0, end = 0;
    printf("Введите начало ценового диапазона за кв.м\n");
    if (!scanf("%f", &start))
        return 1;

    printf("Введите конец ценового диапазона за кв.м\n");
    if (!scanf("%f", &end))
        return 2;

    int counter = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i].square_cost >= start && arr[i].square_cost <= end && !arr[i].type.second.is_pet && !strcmp(arr[i].type_room, "secondary") && arr[i].rooms_quantity == 2)
        {
            printf("Type : %s, Address : %s, Area : %f, Quantity : %d, Cost : %f, Year : %s, Citiz : %d, Pets : %d\n", arr[i].type_room,  arr[i].address, arr[i].area, arr[i].rooms_quantity, arr[i].square_cost, arr[i].type.second.build_year, arr[i].type.second.quantity_prev_owners, arr[i].type.second.is_pet);
            counter++;
        }
    
    }
    if (!counter)
        printf("%s Не найдено ни одного элемента в таком целовом диапазоне и без животных%s\n", RED, RESET);
    
    return 0;
}

void print_record_key(keys_t key)
{
    printf("|%3d|%17d|\n", key.index + 1, key.rooms_quantity);
}

void print_keys(keys_t *keys, int n)
{
    printf("|---------------------|\n");
    printf("| № |  Кол-во комнат  |\n");
    printf("|---------------------|\n");
    for (int i = 0; i < n; i++)
    {
        print_record_key(keys[i]);
    }
    printf("|---------------------|\n");
}

void print_centered_string(const char *str, int width)
{
    int len = strlen(str);
    int padding = (width - len) / 2;
    printf("%*s%s%*s", padding, "", str, width - len - padding, "");
}


void print_centered_int(int value, int width)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d", value); 
    print_centered_string(buffer, width);
}


void print_centered_float(float value, int width)
{
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%.2f", value);  
    print_centered_string(buffer, width);
}

void header()
{
    printf("\n|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
    printf("|    Тип жилья    |      Адрес      |    Площадь     |  Кол-во комнат  |  Стоимость кв.м  |    Отделка   |  Год постройки  | Кол-во предыдущих собственников | Домашние животные |\n");
    printf("|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
}

void footer()
{
    printf("|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|\n");
}

void print_one_record(desc_t room)
{
    if (!strcmp(room.type_room, "primary"))
    {
        printf("|");
        print_centered_string(room.type_room, 17);             
        printf("|");
        print_centered_string(room.address, 17);               
        printf("|");
        print_centered_float(room.area, 16);                   
        printf("|");
        print_centered_int(room.rooms_quantity, 17);           
        printf("|");
        print_centered_float(room.square_cost, 18);            
        printf("|");
        print_centered_string(room.type.prime.trim ? "Есть" : "Нет", 18); 
        printf("|");
        print_centered_string("N/A", 17);                             
        printf("|");
        print_centered_string("N/A", 33);                             
        printf("|");
        print_centered_string("N/A", 19);                             
        printf("|\n");
    }
    else if (!strcmp(room.type_room, "secondary"))
    {
        printf("|");
        print_centered_string(room.type_room, 17);             
        printf("|");
        print_centered_string(room.address, 17);               
        printf("|");
        print_centered_float(room.area, 16);                   
        printf("|");
        print_centered_int(room.rooms_quantity, 17);          
        printf("|");
        print_centered_float(room.square_cost, 18);           
        printf("|");
        print_centered_string("N/A", 14);                      
        printf("|");
        print_centered_string(room.type.second.build_year, 17);   
        printf("|");
        print_centered_int(room.type.second.quantity_prev_owners, 33);  
        printf("|");
        print_centered_int(room.type.second.is_pet ? 1 : 0, 19);   
        printf("|\n");
    }
}

void print_struct(desc_t *arr, int n)
{
    header();
    for (int i = 0; i < n; i++)
    {
        print_one_record(arr[i]);
    }
    footer();
}

void print_structs_by_keys(desc_t *arr, keys_t *keys, int n)
{
    header();
    for (int i = 0; i < n; i++)
    {
        print_one_record(arr[keys[i].index]);
    }
    footer();
}
