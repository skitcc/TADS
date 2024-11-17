#ifndef BUILD_STRUCTS_H
#define BUILD_STRUCTS_H

#include "tree_operations.h"


node_t *build_tree_from_file(const char *filename);
char **build_mas_from_file(const char *filename, int *len);



#endif