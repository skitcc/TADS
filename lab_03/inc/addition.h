#ifndef ADDITION_H
#define ADDITION_H

#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "definitions.h"


CSRMatrixResult add_csr_matrices(const CSRMatrix *matrix1, const CSRMatrix *matrix2);
CSRMatrixResult add_std_matrices(const CSRMatrix *matrix1, const CSRMatrix *matrix2);


#endif