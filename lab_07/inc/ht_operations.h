#ifndef HT_OPERATOINS
#define HT_OPERATOINS


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structs.h"

open_ht* create_open_table(int size);
void insert_open(open_ht *table, const char *word);
char* search_open(open_ht* table, const char* word);
void delete_open(open_ht* table, const char* word);


closed_ht* create_closed_table(int size);
void insert_closed(closed_ht* table, const char* word);
hash_node_t* search_closed(closed_ht* table, const char* word);
void delete_closed(closed_ht* table, const char* word);
void free_closed_table(closed_ht* table);
void free_open_table(open_ht* table);

void read_file_to_hts(const char* filename, closed_ht* closed_table, open_ht* open_table);


#endif
