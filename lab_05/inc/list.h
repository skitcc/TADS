#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include "structs.h"

unsigned long simulate_service_list(struct mem_slot **mem, int *memory_used);
void process_new_request_list(double *total_time, struct queue *queue, struct machine *machine, struct mem_slot **mem);
int process_request_list(struct machine *machine, struct queue *queue, struct mem_slot **mem);
void show_memory_usage(struct mem_slot **mem);
void free_memory_list(struct mem_slot **mem);


#endif