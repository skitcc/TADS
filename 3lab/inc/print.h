#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include "structs.h"
#include "definitions.h"

void print_info(void);
void print_matrix(CSRMatrix *matrix);
void print_csr(CSRMatrix *matrix);
int display_matrix(CSRMatrix *matrix);

#endif