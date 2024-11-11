#ifndef UTILS_H
#define UTILS_H

#include "array.h"
#include "structs.h"
#include "list.h"



double calculate_expected_model_time();
void display_interim_results(struct machine *machine, struct queue *queue);
void display_final_results(struct machine *machine, struct queue *queue, int *memory_used, int max_queue_size);
void advance_queue_pointer(struct queue_slot **pointer, struct queue_slot *array, int length);
void compare_queue_models(struct mem_slot **mem);

#endif