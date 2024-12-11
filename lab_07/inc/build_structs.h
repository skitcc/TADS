#ifndef BUILD_STRUCTS_H
#define BUILD_STRUCTS_H

#include <stdbool.h>

#include "tree_operations.h"
#include "delete_module.h"
#include "utils.h"
#include "visualize_tree.h"
#include "ht_operations.h"


void *build_tree_from_file(const char *filename, int count);

struct tree_interface init_tree_as_avl();
struct tree_interface init_tree_as_bst();

struct ht_interface init_open_table();
struct ht_interface init_closed_table();



#endif  