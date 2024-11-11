#ifndef INPUT_H
#define INPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "definitions.h"
#include "structs.h"

int input_matrix(CSRMatrix *matrix);
int input_std_matrix(CSRMatrix *matrix);
int input_coord_matrix(CSRMatrix *matrix);

#endif