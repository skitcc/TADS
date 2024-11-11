#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "struct.h"


int bubble_sort_structs(desc_t *array, int n, bool *is_sorted);
int bubble_sort_keys(keys_t *keys, int n);
int qsort_structs(desc_t *array, int n, bool *is_sorted);
int qsort_keys(keys_t *keys, int n);


#endif