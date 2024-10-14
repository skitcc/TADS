#include "addition.h"

static void extend_if_needed(CSRMatrix *matrix, int *capacity, int a_index) 
{
    if (a_index >= *capacity) 
    {
        *capacity *= 2;
        matrix->A = (int *)realloc(matrix->A, (*capacity) * sizeof(int));
        matrix->JA = (int *)realloc(matrix->JA, (*capacity) * sizeof(int));
    }
}


CSRMatrixResult add_csr_matrices(const CSRMatrix *matrix1, const CSRMatrix *matrix2)
{
    CSRMatrixResult result = { .error_code = 0 };
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) 
    {
        printf("Ошибка: матрицы должны быть одинакового размера для сложения!\n");
        result.error_code = ERR_NOT_EQUAL_SIZES;
        return result;
    }   

    // Результирующая матрица
    CSRMatrix *matrix_result = &result.matrix;
    matrix_result->rows = matrix1->rows;
    matrix_result->cols = matrix1->cols;
    matrix_result->nnz = 0;

    int capacity = 10;
    matrix_result->A = (int *)malloc(capacity * sizeof(int));
    matrix_result->JA = (int *)malloc(capacity * sizeof(int));
    matrix_result->IA = (int *)calloc((matrix_result->rows + 1), sizeof(int));

    if (matrix_result->A == NULL || matrix_result->JA == NULL || matrix_result->IA == NULL) 
    {
        result.error_code = ERR_ALLOCATION;
        return result;
    }

    int current_a = 0;
    for (int i = 0; i < matrix_result->rows; i++) {
        int idx1 = matrix1->IA[i];
        int idx2 = matrix2->IA[i];
        matrix_result->IA[i] = current_a;

        while (idx1 < matrix1->IA[i + 1] || idx2 < matrix2->IA[i + 1]) {
            int col1 = (idx1 < matrix1->IA[i + 1]) ? matrix1->JA[idx1] : matrix_result->cols;
            int col2 = (idx2 < matrix2->IA[i + 1]) ? matrix2->JA[idx2] : matrix_result->cols;
            int value = 0;

            if (col1 == col2) {
                value = matrix1->A[idx1] + matrix2->A[idx2];
                idx1++;
                idx2++;
            } else if (col1 < col2) {
                value = matrix1->A[idx1];
                col2 = col1;
                idx1++;
            } else {
                value = matrix2->A[idx2];
                col1 = col2;
                idx2++;
            }

            if (value != 0) {
                extend_if_needed(matrix_result, &capacity, current_a);
                matrix_result->A[current_a] = value;
                matrix_result->JA[current_a] = col1;
                current_a++;
            }
        }
    }
    matrix_result->IA[matrix_result->rows] = current_a;
    matrix_result->nnz = current_a;

    return result;
}

CSRMatrixResult add_std_matrices(const CSRMatrix *matrix1, const CSRMatrix *matrix2) {

    CSRMatrixResult result = { .error_code = 0 };
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols) {
        printf("Ошибка: матрицы должны быть одинакового размера для сложения!\n");
        result.error_code = ERR_NOT_EQUAL_SIZES;
        return result;
    }

    CSRMatrix *result_matrix = &result.matrix;
    result_matrix->rows = matrix1->rows;
    result_matrix->cols = matrix1->cols;
    result_matrix->nnz = 0;

    int capacity = 10;
    result_matrix->A = (int *)malloc(capacity * sizeof(int));
    result_matrix->JA = (int *)malloc(capacity * sizeof(int));
    result_matrix->IA = (int *)calloc((result_matrix->rows + 1), sizeof(int));

    int current_a = 0;

    for (int i = 0; i < result_matrix->rows; i++) {
        result_matrix->IA[i] = current_a;

        for (int j = 0; j < result_matrix->cols; j++) {
            int value = 0;

            for (int idx1 = matrix1->IA[i]; idx1 < matrix1->IA[i + 1]; idx1++) {
                if (matrix1->JA[idx1] == j) {
                    value += matrix1->A[idx1];
                    break;
                }
            }

            for (int idx2 = matrix2->IA[i]; idx2 < matrix2->IA[i + 1]; idx2++) {
                if (matrix2->JA[idx2] == j) {
                    value += matrix2->A[idx2];
                    break;
                }
            }

            if (value != 0) {
                extend_if_needed(result_matrix, &capacity, current_a);
                result_matrix->A[current_a] = value;
                result_matrix->JA[current_a] = j;
                current_a++;
            }
        }
    }
    result_matrix->IA[result_matrix->rows] = current_a;
    result_matrix->nnz = current_a;

    return result;
}
