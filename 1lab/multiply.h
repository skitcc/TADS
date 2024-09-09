#ifndef MULTIPLY_H
#define MULTIPLY_H

#include "definitions.h"
#include "struct.h"

#include <stdlib.h>
#include <string.h>

void reverse_num(char *num);
void remove_dot(double_data *double_num, size_t *diff);
void matrix_generator(double_data *double_num, int_data *int_num, result_data *result_num);
void print_matrix(int matrix[MAX_LEN_ROW][MAX_LEN_COLUMN], size_t rows, size_t cols);
void matrix_solver(int matrix[][MAX_LEN_COLUMN], size_t rows, size_t cols, int *result_mas, size_t *len_arr);
int form_result(int *result_mas, size_t len, size_t diff_dot, result_data *result_num, double_data *double_num);


#endif