#include <stdio.h>
#include <inttypes.h>
#include "structs.h"
#include "graph_operations.h"
#include "visualise_graph.h"
#include "print.h"


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

int main() 
{
    const char* filename = "graph.txt";
    Graph* graph = NULL;
    print_menu();

    PRINT_COLOR(VIOLET, "Введите опцию");
    int option;
    if (scanf("%d", &option) != 1 || option < 0 || option > 4)
    {
        PRINT_COLOR(RED, "Ошибка ввода опции!");
        return 1;
    }
    int count = 0;
    while (option)
    {
        switch (option)
        {
        case 1:
        {
            uint64_t start = tick_count();
            graph = read_graph_from_file(filename, &count);
            uint64_t end = tick_count();

            printf("Время выполнения для чтения графа из файла: %" PRIu64 " тактов\n", end - start);
            printf("Память для представления графа : %d байт\n", count * 16);
            export_graph(graph, "./data/exp_graph.dot");
            break;
        }
        case 2:
        {
            if (graph == NULL)
            {
                PRINT_COLOR(RED, "Граф пустой!");
                break;
            }
            uint64_t start = tick_count();
            find_max_paths(graph);
            uint64_t end = tick_count();
            printf("Время выполнения для поиска максимальных путей: %" PRIu64 " тактов\n", end - start);
            break;
        }
        case 3:
        {
            if (graph == NULL)
            {
                PRINT_COLOR(RED, "Граф пустой!");
                break;
            }

            uint64_t start = tick_count();
            bool result = is_graph_connected(graph);
            uint64_t end = tick_count();
            if (result) 
                printf("Граф сильно связный.\n");
            else
                printf("Граф не сильно связный.\n");
            printf("Время выполнения для проверки на связность: %" PRIu64 " тактов\n", end - start);

            break;
        }
        case 4:
        {
            if (graph == NULL)
            {
                PRINT_COLOR(RED, "Граф пустой!");
                break;
            }
            uint64_t start = tick_count();
            printf("Вес минимального остовного дерева: %d\n", kruskal_MST(graph));
            uint64_t end = tick_count();
            printf("Время выполнения для нахождения остовного дерева: %" PRIu64 " тактов\n", end - start);
            break;
        }
        case 0:
        {
            PRINT_COLOR(GREEN, "Завершение программы!");
            return 0;
        }
        default:
            break;

        }
        print_menu();
        PRINT_COLOR(VIOLET, "Введите опцию");
        if (scanf("%d", &option) != 1 || option < 0 || option > 4)
        {
            PRINT_COLOR(RED, "Ошибка ввода опции!");
            return 1;
        }
    }



    return 0;
}
