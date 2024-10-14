#include <stdio.h>
#include <stdlib.h>

#include "print.h"
#include "definitions.h"
#include "structs.h"
#include "input.h"
#include "addition.h"
#include "time_memory_comp.h"
#include "utils.h"



int main() {
    CSRMatrix matrix1 = { .A = NULL, .JA = NULL, .IA = NULL }; 
    CSRMatrix matrix2 = { .A = NULL, .JA = NULL, .IA = NULL }; 

    int mode = -1; 

    while (mode != 0) {  
        print_info();  

        printf("Введите режим работы (0 для выхода):\n");

        if (scanf("%d", &mode) != 1) 
        {
            printf("%sОшибка: неверная опция! Пожалуйста, введите корректный режим.%s\n", RED, RESET);

            while (getchar() != '\n');  

            mode = -1; 
            continue;   
        }

        switch (mode) 
        {
            case 1:
                printf("Введите первую матрицу\n");
                if (input_matrix(&matrix1)) 
                {
                    printf("%sОшибка ввода первой матрицы!%s\n", RED, RESET);
                    continue;
                }
                printf("%sПервая матрица успешно считана%s\n", GREEN, RESET);

                printf("Введите вторую матрицу\n");
                if (input_matrix(&matrix2)) 
                {
                    printf("%sОшибка ввода второй матрицы!%s\n", RED, RESET);
                    free_matrix(&matrix1);
                    continue;
                }
                printf("%sВторая матрица успешно считана%s\n", GREEN, RESET);
                break;

            case 2:
                printf("Первая входная матрица\n");
                if (display_matrix(&matrix1)) 
                {
                    printf("%sОшибка отображения первой матрицы!%s\n", RED, RESET);
                    continue;
                }

                printf("Вторая входная матрица\n");
                if (display_matrix(&matrix2)) 
                {
                    printf("%sОшибка отображения второй матрицы!%s\n", RED, RESET);
                    free_matrix(&matrix1);
                    free_matrix(&matrix2);
                    continue;
                }
                break;

            case 3: 
            {
                CSRMatrixResult result = add_std_matrices(&matrix1, &matrix2);
                if (result.error_code) 
                {
                    printf("%sОшибка при сложении матриц стандартным алгоритмом!%s\n", RED, RESET);
                    continue;
                }

                printf("%sМатрицы успешно сложены стандартным алгоритмом!%s\n", GREEN, RESET);
                printf("Результирующая матрица, полученная сложением двух матриц стандартным алгоритмом:\n");
                CSRMatrix *result_for_display = &result.matrix;
                if (display_matrix(result_for_display)) 
                {
                    free_matrix(result_for_display);
                    continue;
                }
                free_matrix(result_for_display);
                break;
            }

            case 4: 
            {
                CSRMatrixResult result = add_csr_matrices(&matrix1, &matrix2);
                if (result.error_code) 
                {
                    printf("%sОшибка при сложении матриц в формате CSR!%s\n", RED, RESET);
                    continue;
                }

                printf("%sМатрицы успешно сложены в формате CSR!%s\n", GREEN, RESET);
                printf("Результирующая матрица, полученная сложением двух матриц в формате CSR:\n");
                CSRMatrix *result_for_display = &result.matrix;
                if (display_matrix(result_for_display)) 
                {
                    free_matrix(result_for_display);
                    continue;
                }
                free_matrix(result_for_display);
                break;
            }

            case 5: 
            {
                printf("Введите кол-во матриц, на замеры которых вы бы хотели посмотреть\n");
                int n = 0;
                if (!scanf("%d", &n) || n <= 0)
                {
                    printf("%sОшибка ввода числа матриц!%s\n", RED, RESET);
                    continue;
                }
                
                MatrixParams *matrices = (MatrixParams *)malloc(n * sizeof(MatrixParams));
                if (matrices == NULL)
                {
                    printf("%sОшибка выделения памяти!%s\n", RED, RESET);
                    return 1;
                }

                for (int i = 0; i < n; i++) {
                    printf("Введите параметры для матриц %d (строки, столбцы, процент заполнения): ", i + 1);
                    if (scanf("%d %d %d", &matrices[i].rows, &matrices[i].cols, &matrices[i].percent) != 3) {
                        printf("%sОшибка ввода параметров матрицы!%s\n", RED, RESET);
                        free(matrices);
                        return 1;
                    }
                }

                printf("\nПараметры введенных матриц:\n");
                for (int i = 0; i < n; i++) {
                    printf("%sМатрица %d: %d строк, %d столбцов, %d%% заполнение%s\n",
                        YELLOW, i + 1, matrices[i].rows, matrices[i].cols, matrices[i].percent, RESET);
                }


                for (int i = 0; i < n; i++)
                {
                    printf("%sРезультаты для %d параметров%s\n", GREEN, i, RESET);
                    compare_algorithms(matrices[i].rows, matrices[i].cols, matrices[i].percent);
                }
                free(matrices);
                break;
            }

            case 0:
                printf("Завершение программы.\n");
                break;

            default:
                printf("%sНеправильный режим работы. Пожалуйста, выберите корректный режим.%s\n", RED, RESET);
                break;
        }
    }

    free_matrix(&matrix1);
    free_matrix(&matrix2);

    return 0;
}
