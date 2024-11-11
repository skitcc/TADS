#include "utils.h"



void free_matrix(CSRMatrix *matrix) 
{
    if (matrix->A) free(matrix->A);
    if (matrix->JA) free(matrix->JA);
    if (matrix->IA) free(matrix->IA);

    matrix->A = NULL;  
    matrix->JA = NULL;
    matrix->IA = NULL;
}

int** create_dense_matrix(int rows, int cols, int fill_percentage) 
{
    int total_elements = rows * cols;
    int nnz = (total_elements * fill_percentage) / 100; 
    int **matrix = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int *)calloc(cols, sizeof(int)); 
    }

    int *positions = (int *)malloc(total_elements * sizeof(int));
    for (int i = 0; i < total_elements; i++) {
        positions[i] = i;
    }

    for (int i = total_elements - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = positions[i];
        positions[i] = positions[j];
        positions[j] = temp;
    }

    for (int i = 0; i < nnz; i++) {
        int idx = positions[i];
        int row = idx / cols;
        int col = idx % cols;
        matrix[row][col] = rand() % 10 + 1;
    }

    free(positions);
    return matrix;
}


void convert_to_csr(int **dense_matrix, int rows, int cols, CSRMatrix *csr) 
{
    csr->rows = rows;
    csr->cols = cols;
    csr->nnz = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dense_matrix[i][j] != 0) {
                csr->nnz++;
            }
        }
    }

    csr->A = (int *)malloc(csr->nnz * sizeof(int));
    csr->JA = (int *)malloc(csr->nnz * sizeof(int));
    csr->IA = (int *)malloc((rows + 1) * sizeof(int));

    int nnz_counter = 0;
    csr->IA[0] = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (dense_matrix[i][j] != 0) {
                csr->A[nnz_counter] = dense_matrix[i][j];
                csr->JA[nnz_counter] = j;
                nnz_counter++;
            }
        }
        csr->IA[i + 1] = nnz_counter;
    }
}


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