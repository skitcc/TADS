#include "print.h"


void print_menu()
{
    PRINT_COLOR(TURQ, "1 - Считывание взвешенного графа из файла");
    PRINT_COLOR(TURQ, "2 - Поиск максимальных простых путей для каждой пары вершин");
    PRINT_COLOR(TURQ, "3 - Проверка на связность графа");
    PRINT_COLOR(TURQ, "4 - Построение остовного дерева");
    PRINT_COLOR(TURQ, "0 - Выход из программы");
}