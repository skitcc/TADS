#include "input.h"

int validate_year(char *year)
{
    const char pattern[] = "^(0[1-9]|[12][0-9]|3[01]).(0[1-9]|1[0-2]).[0-9]{4}$";
    regex_t regex;

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0)
        return ERROR_MATCHING_REG_EXPR;

    if (regexec(&regex, year, 0, NULL, 0) != 0)
    {
        printf("Год не соответствует формату!\n");
        return ERROR_MATCHING_REG_EXPR;
    }
    return 0;

}

// mode = 1 - stdin ; mode = 0 - file
int read_one_record(desc_t *record, FILE *f_in, short mode)
{

    if (mode)
        printf("Введите тип квартиры \n1. primary(первичное)\n2. secondary(вторичное)\n");
    

    if (!fscanf(f_in, "%s", record->type_room) && (strcmp(record->type_room, "primary") == 0 || strcmp(record->type_room, "secondary") == 0))
    {
        printf("Ошибка чтения типа комнаты\n");
        return ERROR_READING_TYPE_ROOM;
    }
    if (mode)
        printf("Введите адрес квартиры без пробелов!\n");
    
    if (!fscanf(f_in, "%s", record->address))
    {
        printf("Ошибка чтения адреса!\n");
        return ERROR_READING_ADDRESS;
    }
    if (mode)
        printf("Введите площадь квартиры в кв.м (целое/вещественное) число\n");

    if (!fscanf(f_in, "%f", &record->area) || record->area < 0)
    {
        printf("Ошибка чтения площади квартиры!\n");
        return ERROR_READING_SQUARE;
    }
    if (mode)
        printf("Введите кол-во комнат (целое число)\n");

    if (!fscanf(f_in, "%d", &record->rooms_quantity))
    {
        printf("Ошибка чтения количества комнат!\n");
        return ERROR_READING_AMOUNT_ROOMS;
    }

    if (mode)
        printf("Введите цену за квадратный метр\n");

    if (!fscanf(f_in, "%f", &record->square_cost))
    {
        printf("Ошибка чтения цены за квадратный метр!\n");
        return ERROR_READING_COST;
    }


    if (!strcmp(record->type_room, "primary"))
    {
        if (mode)
            printf("Введите есть ли в квартире отделка или нет (1/0)\n");
        if (!fscanf(f_in, "%hd", &record->type.prime.trim))
        {
            printf("Ошибка чтения параметра отделки!\n");
            return ERROR_READING_TRIM;
        }
    }
    
    if (!strcmp(record->type_room, "secondary"))
    {
        if (mode)
            printf("Введите год постройки квартиры в формате dd.mm.yyyy\n");

        if (!fscanf(f_in, "%s", record->type.second.build_year))
        {
            printf("Ошибка чтения года постройки!\n");
            return ERROR_READING_YEAR;
        }
        if (validate_year(record->type.second.build_year))
            return ERROR_MATCHING_REG_EXPR;

        if (mode)
            printf("Введите количество предыдущих собственников\n");

        if (!fscanf(f_in, "%d", &record->type.second.quantity_prev_owners) || record->type.second.quantity_prev_owners < 0)
        {
            printf("Ошибка чтения количества предыдущих собственников!\n");
            return ERROR_READING_LAST_OWNERS;
        }

        if (mode)
            printf("Введите были ли животные в этой квартире (0 - не были, 1 - были)\n");

        if (!fscanf(f_in, "%hd", &record->type.second.is_pet))
        {
            printf("Ошибка чтения питомцев!\n");
            return ERROR_READING_PETS;
        }  

        if (record->type.second.is_pet < 0 || record->type.second.is_pet > 1)
        {
            printf("Значение питомцев может быть 0 или 1!\n");
            return ERROR_VALUE_PETS;
        }

    }
    return 0;

}