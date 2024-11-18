#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "structs.h"
#include "utils.h"

node_t *create_node(char *value);
node_t *insert(node_t *root, char *value);
node_t *delete_node(node_t *node);
node_t *search_node(node_t *node, const char *value);
void prefix_traversal(node_t *root, bool is_measuring);
void infix_traversal(node_t *root, bool is_measuring);
void postfix_traversal(node_t *root, bool is_measuring);

#endif