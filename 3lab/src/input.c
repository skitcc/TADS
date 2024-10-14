#include "input.h"


int input_matrix(CSRMatrix *matrix) {
    char variant_input;
    printf("Выберите способ заполнения матрицы, введите 0 - стандартный, введите 1 - координатный\n");
    if (!scanf(" %c", &variant_input)) 
        return ERR_INPUT;

    int rc;
    if (variant_input == '0' && (rc = input_std_matrix(matrix)))
        return rc;
    else if (variant_input == '1' && (rc = input_coord_matrix(matrix)))
        return rc;
    else if (variant_input != '1' && variant_input != '0') {
        printf("%sНеправильная опция ввода матрицы!%s\n", RED, RESET);
        return 2;
    }

    return 0;
}

int check_args(int *rows, int *cols)
{
    printf("Введите кол-во строк и столбцов для матрицы\n");
    if (scanf("%d%d", rows, cols) != 2)
    {
        return ERR_INPUT;
    }
    if (*cols < 0 || *rows < 0)
    {
        return ERR_SIZE;
    }
    return EXIT_SUCCESS;
}

static void extend_if_needed(CSRMatrix *matrix, int *capacity, int a_index) 
{
    if (a_index >= *capacity) 
    {
        *capacity *= 2;
        matrix->A = (int *)realloc(matrix->A, (*capacity) * sizeof(int));
        matrix->JA = (int *)realloc(matrix->JA, (*capacity) * sizeof(int));
    }
}


int input_std_matrix(CSRMatrix *matrix)
{
    int rc;
    if ((rc = check_args(&matrix->rows, &matrix->cols)))
        return rc;

    int capacity = 10;

    matrix->A = (int *)malloc(capacity * sizeof(int));
    matrix->JA = (int *)malloc(capacity * sizeof(int));
    matrix->IA = (int *)malloc((matrix->rows + 1) * sizeof(int));


    int current_a = 0;
    matrix->IA[0] = 0;

    for (int i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->cols; j++)
        {
            int value = 0;
            if (!scanf("%d", &value))
                return ERR_INPUT;

            if (value)
            {
                extend_if_needed(matrix, &capacity, current_a);
                matrix->A[current_a] = value;
                matrix->JA[current_a] = j;
                current_a++;
            }
        }
        matrix->IA[i + 1] = current_a;
    }
    matrix->nnz = current_a;
    return 0;
    
}

int input_coord_matrix(CSRMatrix *matrix) {
    int capacity = 10;
    int rc;

    // Запрашиваем количество строк и столбцов
    if ((rc = check_args(&matrix->rows, &matrix->cols)))
        return rc;

    int total_nnz;
    printf("Введите общее количество ненулевых элементов в матрице: ");
    if (!scanf("%d", &total_nnz))
        return ERR_INPUT;
    if (total_nnz < 0 || total_nnz > matrix->rows * matrix->cols)
        return ERR_NZE;

    // Выделяем память для A, JA и IA
    matrix->A = (int *)malloc(capacity * sizeof(int));
    matrix->JA = (int *)malloc(capacity * sizeof(int));
    matrix->IA = (int *)calloc((matrix->rows + 1), sizeof(int));

    int current_a = 0;

    // Временный массив для подсчета количества ненулевых элементов в каждой строке
    int *row_nnz = (int *)calloc(matrix->rows, sizeof(int));

    for (int i = 0; i < total_nnz; i++) {
        int row, col, value;

        printf("Введите строку, столбец и значение ненулевого элемента %d (например: 0 1 5): ", i + 1);
        if (scanf("%d %d %d", &row, &col, &value) != 3)
            return ERR_INPUT;
        if (row < 0 || row >= matrix->rows || col < 0 || col >= matrix->cols)
            return ERR_COORDS;

        if (value) {
            // Увеличиваем массивы, если нужно
            extend_if_needed(matrix, &capacity, current_a);

            // Заполняем A и JA
            matrix->A[current_a] = value;
            matrix->JA[current_a] = col;
            current_a++;

            // Увеличиваем счетчик ненулевых элементов в строке
            row_nnz[row]++;
        }
    }

    // Построение массива IA
    for (int i = 1; i <= matrix->rows; i++) {
        matrix->IA[i] = matrix->IA[i - 1] + row_nnz[i - 1];
    }

    // Освобождаем временный массив
    free(row_nnz);

    matrix->nnz = current_a;

    return 0;
}
