#ifndef DELETE_MODULE_H
#define DELETE_MODULE_H



#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <ctype.h>


#include "structs.h"
#include "utils.h"
#include "tree_operations.h"


void *delete_nodes_starting_with_non_balanced(void *head, char start_char, int *comparisons);
void *delete_nodes_starting_with_balanced(void *head, char start_char, int *comparisons);

#endif