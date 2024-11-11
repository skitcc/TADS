#ifndef UTILS_H
#define UTILS_H

#include "structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>



void free_matrix(CSRMatrix *matrix);
int** create_dense_matrix(int rows, int cols, int fill_percentage);
void convert_to_csr(int **dense_matrix, int rows, int cols, CSRMatrix *csr);
uint64_t tick_count(void);

#endif