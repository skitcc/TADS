#include "print.h"

void print_info(void)
{
    printf("Выберите одну из доступных опций\n");
    printf("1 - Ввод матриц\n");
    printf("2 - Вывод входных матриц\n");
    printf("3 - Сложение матриц стандартным алгоритмом\n");
    printf("4 - Сложение матриц алгоритмом CSR\n");
    printf("5 - Сравнение времени работы и памяти при разном проценте заполнения матриц для стандартного и сокращенного метода сложения\n");
}


void print_matrix(CSRMatrix *matrix) 
{
    printf("Матрица в обычном формате:\n");
    for (int i = 0; i < matrix->rows; i++) 
    {
        int idx = matrix->IA[i];
        for (int j = 0; j < matrix->cols; j++) 
        {
            if (idx < matrix->IA[i + 1] && matrix->JA[idx] == j) 
            {
                printf("%d ", matrix->A[idx]);
                idx++;
            } else 
                printf("0 ");
            
        }
        printf("\n");
    }
}

void print_csr(CSRMatrix *matrix) 
{
    printf("Матрица в формате CSR:\n");

    printf("A (значения ненулевых элементов):\n");
    for (int i = 0; i < matrix->nnz; i++) {
        printf("%d ", matrix->A[i]);
    }
    printf("\n");

    printf("JA (номера столбцов):\n");
    for (int i = 0; i < matrix->nnz; i++) {
        printf("%d ", matrix->JA[i]);
    }
    printf("\n");

    printf("IA (индексы начала строк):\n");
    for (int i = 0; i <= matrix->rows; i++) {
        printf("%d ", matrix->IA[i]);
    }
    printf("\n");
}

int display_matrix(CSRMatrix *matrix) 
{
    char variant_input;
    printf("Введите формат отображения матрицы: 1 - обычный, 2 - в формате CSR\n");
    if (!scanf(" %c", &variant_input)) 
        return ERR_INPUT;

    if (variant_input == '1') {
        print_matrix(matrix);
    } else if (variant_input == '2') {
        print_csr(matrix);
    } else {
        printf("%sНеправильная опция отображения матрицы!%s\n", RED, RESET);
        return 2;
    }

    return 0;
}