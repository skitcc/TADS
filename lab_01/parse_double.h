#ifndef PARSE_DOUBLE_H
#define PARSE_DOUBLE_H

#include "definitions.h"
#include "struct.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <regex.h>


int mantissa_check(char *input, double_data *data);


#endif