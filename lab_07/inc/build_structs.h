#ifndef BUILD_STRUCTS_H
#define BUILD_STRUCTS_H

#include <stdbool.h>

#include "tree_operations.h"
#include "delete_module.h"
#include "utils.h"
#include "visualize_tree.h"


void *build_tree_from_file(const char *filename);

struct tree_interface init_tree_as_avl();
struct tree_interface init_tree_as_bst();


#endif  