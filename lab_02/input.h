#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <regex.h>
#include <string.h>
#include "definitions.h"
#include "struct.h"

int read_one_record(desc_t *record, FILE *f_in, short mode);

#endif