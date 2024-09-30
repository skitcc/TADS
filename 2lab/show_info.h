#ifndef SHOW_INFO_H
#define SHOW_INFO_H


#include <stdio.h>
#include <string.h>
#include "struct.h"
#include "definitions.h"


void show_options(void);
void print_structs_by_keys(desc_t *arr, keys_t *keys, int n);
int print_task_version(desc_t *arr, int n);
void print_keys(keys_t *keys, int n);
void print_struct(desc_t *arr, int n);

#endif