#ifndef ARRAY_H
#define ARRAY_H

#include "structs.h"
#include "time_mem.h"
#include "utils.h"

unsigned long simulate_service_arr(int *memory_used);
void process_new_request_arr(double *total_time, struct machine *machine, struct queue *queue, struct queue_slot *array, int max_queue_size);
int process_request_arr(struct machine *machine, struct queue *queue, struct queue_slot *array, int array_length);
#endif