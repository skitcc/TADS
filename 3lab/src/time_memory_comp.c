#include "time_memory_comp.h"


void compare_algorithms(int rows, int cols, int fill_percentage) 
{
    srand(time(NULL));  
    CSRMatrix matrix1, matrix2;
    int **dense_matrix1 = create_dense_matrix(rows, cols, fill_percentage);

    printf("%sМатрица 1, %d строк, %d столбцов, %d%% заполнение %s\n",GREEN,rows,cols,fill_percentage, RESET);
    convert_to_csr(dense_matrix1, rows, cols, &matrix1);
    
    int option = 0;
    printf(BLUE "Просмотр матрицы (0 - нет, 1 - да)\n" RESET);
    if (!scanf("%d", &option)) {
        printf(RED "Ошибка ввода опции просмотра матрицы!\n" RESET);
        return;
    }
    if (option == 1)
        display_matrix(&matrix1); 
    else if (option == 0)
        printf(YELLOW "Матрица не отображена!\n" RESET);
    else
        return;

    int **dense_matrix2 = create_dense_matrix(rows, cols, fill_percentage);
    printf("%sМатрица 2, %d строк, %d столбцов, %d%% заполнение %s\n",GREEN,rows,cols,fill_percentage, RESET);
    convert_to_csr(dense_matrix2, rows, cols, &matrix2);

    printf(BLUE "Просмотр матрицы (0 - нет, 1 - да)\n" RESET);
    if (!scanf("%d", &option)) {
        printf(RED "Ошибка ввода опции просмотра матрицы!\n" RESET);
        return;
    }
    if (option == 1)
        display_matrix(&matrix2); 
    else if (option == 0)
        printf(YELLOW "Матрица не отображена!\n" RESET);
    else
        return;         

    uint64_t total_ticks_std = 0, total_ticks_csr = 0;
    CSRMatrixResult std_result;
    CSRMatrix *final_std_result = NULL;  

    printf(GREEN "\nСложение стандартным алгоритмом (процент заполнения: %d%%):\n" RESET, fill_percentage);
    for (int i = 0; i < REPEAT_COUNT; i++) {
        uint64_t start_ticks = tick_count();
        std_result = add_std_matrices(&matrix1, &matrix2);
        uint64_t end_ticks = tick_count();
        total_ticks_std += (end_ticks - start_ticks);
        if (std_result.error_code) {
            printf(RED "Ошибка при сложении матриц стандартным методом!\n" RESET);
            return;
        }

        if (i == REPEAT_COUNT - 1) {
            final_std_result = &std_result.matrix;  
        } else {
            free(std_result.matrix.A);
            free(std_result.matrix.JA);
            free(std_result.matrix.IA);
        }
    }

    printf(BLUE "Просмотр результата сложения матриц стандартным методом? (0 - нет, 1 - да)\n" RESET);
    if (!scanf("%d", &option)) {
        printf(RED "Ошибка ввода опции просмотра матрицы!\n" RESET);
        return;
    }
    if (option == 1)
        display_matrix(final_std_result); 
    else if (option == 0)
        printf(YELLOW "Матрица не отображена!\n" RESET);
    else
        return;    

    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, total_ticks_std / REPEAT_COUNT);
    printf(YELLOW "Объем памяти для стандартной матрицы: %ld байт\n" RESET, rows * cols * sizeof(int));

    CSRMatrixResult csr_result;
    CSRMatrix *final_csr_result = NULL;
    printf(GREEN "\nСложение в формате CSR (процент заполнения: %d%%):\n" RESET, fill_percentage);
    for (int i = 0; i < REPEAT_COUNT; i++) {
        uint64_t start_ticks = tick_count();
        csr_result = add_csr_matrices(&matrix1, &matrix2);
        uint64_t end_ticks = tick_count();
        total_ticks_csr += (end_ticks - start_ticks);

        if (csr_result.error_code) {
            printf(RED "Ошибка при сложении матриц методом CSR!\n" RESET);
            return;
        }

        if (i == REPEAT_COUNT - 1) {
            final_csr_result = &csr_result.matrix;
        } else {
            free(csr_result.matrix.A);
            free(csr_result.matrix.JA);
            free(csr_result.matrix.IA);
        }
    }

    printf(BLUE "Просмотр результата сложения матриц в формате CSR? (0 - нет, 1 - да)\n" RESET);
    if (!scanf("%d", &option)) {
        printf(RED "Ошибка ввода опции просмотра матрицы!\n" RESET);
        return;
    }
    if (option == 1)
        display_matrix(final_csr_result); 
    else if (option == 0)
        printf(YELLOW "Матрица не отображена!\n" RESET);
    else
        return;    

    printf(YELLOW "Такты: %" PRIu64 "\n" RESET, total_ticks_csr / REPEAT_COUNT);    

    size_t csr_memory = final_csr_result->nnz * sizeof(int)   
                    + final_csr_result->nnz * sizeof(int)   
                    + (final_csr_result->rows + 1) * sizeof(int);

    printf(YELLOW "Объем памяти для CSR матрицы: %ld байт\n" RESET, csr_memory);

    if (final_std_result != NULL) 
        free_matrix(final_std_result);
    

    if (final_csr_result != NULL) 
        free_matrix(final_csr_result);

    free_matrix(&matrix1);
    free_matrix(&matrix2);
}
