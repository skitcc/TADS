#ifndef HANDLE_OPTIONS_H
#define HANDLE_OPTIONS_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "definitions.h"
#include "tree_operations.h"
#include "utils.h"
#include "visualize_tree.h"
#include "delete_module.h"
#include "build_structs.h"
#include "timing.h"
#include "print.h"



void handle_generate_file(const char *file_in);
void handle_generate_tree(node_t **root, const char *file_in);
void handle_export_tree(node_t *root);
void handle_traversal(node_t *root);
void handle_insert_node(node_t **root);
void handle_delete_nodes(node_t **root);
void handle_compare_time(const char *file_in);
void handle_search_node(node_t *root);
void handle_cleanup(const char *file_in, node_t **root);
void handle_exit(const char *file_in, node_t *root);



#endif