#ifndef DISTRIBUTE_H
#define DISTRIBUTE_H

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int distribute_to_double_data(double_data *double_num, char *double_str, size_t len);
void distribute_to_int_data(int_data *int_num, char *int_str, size_t len);



#endif