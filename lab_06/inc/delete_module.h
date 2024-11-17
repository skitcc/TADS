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
#include <ctype.h>




#include "structs.h"


node_t *delete_nodes_starting_with(node_t *root, char start_char);
node_t *delete_node_by_value(node_t *root, const char *value);
node_t *delete_node(node_t *node);
int delete_elems_starts_with_sorted(char **mas, int len, char start_char);
int delete_elems_starts_with(char **mas, int len, char start_char);

#endif