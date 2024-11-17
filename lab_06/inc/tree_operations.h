#ifndef TREE_OPERATIONS_H
#define TREE_OPERATIONS_H


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "structs.h"

node_t *create_node(char *value);
node_t *insert(node_t *root, char *value);


#endif