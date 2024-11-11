#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "definitions.h"
#include "struct.h"
#include "input.h"


int load_data(desc_t *arr, int *n, keys_t *keys);
int add_data(desc_t *arr, int *n, keys_t *keys);
int delete_data(desc_t *arr, int *n, keys_t *keys);


#endif