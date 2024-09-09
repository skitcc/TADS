#ifndef PARSE_DOUBLE_H
#define PARSE_DOUBLE_H

#include "definitions.h"
#include "struct.h"


short before_dot_check(char *my_double, char *mantissa, size_t *i_m, size_t *ind_format, short *flag);
short exp_check(char *my_double, size_t *i_m, char *sign_exp);
short order_check(char *my_double, size_t *k);
void fill_after_dot(char *my_double, char *temp_str, size_t *i_m, size_t *temp_ind, short *flag);
short check_mantiss(char *my_double, double_data *whole_num);






#endif