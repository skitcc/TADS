#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "structs.h"



void free_tree(node_t *root);
void print_tree(node_t *root, int depth, const char *relation);
void debug_tree_structure(node_t *root);
void print_mas(char **mas, int len);
void free_mas(char **mas, int len);
void gen_data_file(const char *filename);

#endif