#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "structs.h"
#include "definitions.h"


void free_tree_bst(void *head);
void free_tree_avl(void *head);
void gen_data_file(const char *filename, int len);
int clean_file(const char *filename);
void free_node_bst(bst_t *node);
void free_node_avl(avl_t *node);
bst_t *find_min_bst(bst_t *root);
avl_t *find_min_avl(avl_t *root); 
void print_tree(avl_t *root, int depth, const char *relation);

#endif
