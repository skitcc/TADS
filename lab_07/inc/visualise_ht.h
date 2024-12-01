#ifndef VISUALISE_HT_H
#define VISUALISE_HT_H


#include <stdio.h>
#include <stdlib.h>

#include "structs.h"
#include "definitions.h"

void visualize_closed(closed_ht* table, const char* filename);
void visualize_open(open_ht* table, const char* filename);

#endif