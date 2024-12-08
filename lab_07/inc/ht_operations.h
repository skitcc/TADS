#ifndef HT_OPERATOINS
#define HT_OPERATOINS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

void *create_open_table(int size);
void insert_open(void *root, const char *word);
void *search_open(void *root, const char* word);
void delete_open(void *root, const char* word);
void print_comparisons_open(void *root);



void *create_closed_table(int size);
void insert_closed(void *root, const char* word);
void* search_closed(void *root, const char* word);
void delete_closed(void *root, const char* word);
void print_comparisons_closed(void *root);
void check_and_restructure(closed_ht *ht);


void free_closed_table(void *table);
void free_open_table(void* table);


void print_ht_open(void *root);
void print_ht_closed(void *root);


void read_file_to_hts(const char* filename, closed_ht* closed_table, open_ht* open_table);


#endif
