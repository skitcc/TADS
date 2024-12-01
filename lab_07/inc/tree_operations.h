#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "utils.h"


bst_t *create_node_bst(char *value);
void *insert_bst(void *head, char *value);
bst_t *delete_node_bst(bst_t *node);
void *search_node_bst(void *head, const char *value, int *comparisons);
void prefix_traversal_bst(void *head, bool is_measuring);


avl_t *balance_tree(bst_t *root);
avl_t *create_node_avl(const char *value);
void *insert_avl(void *head, const char *value);
void *search_node_avl(void *head, const char *value, int *comparisons);
void *delete_node_avl(void *head);
void prefix_traversal_avl(void *head, bool is_measuring);





#endif