#ifndef TIME_MEM_H
#define TIME_MEM_H

#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "definitions.h"
#include "structs.h"


unsigned long long tick(void);
double get_time(int t1, int t2);
int chance(void);
void add_mem(struct queue_slot *slot, struct mem_slot **mem);
void delete_mem(struct queue_slot *slot, struct mem_slot *mem);


#endif