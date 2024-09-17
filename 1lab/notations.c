#include "notations.h"

// Проверка, что число уже в правильном формате ±m.nE±K
int is_valid_scientific_notation(const char *str, char *new_str) {
    size_t len = strlen(str);
    size_t i = 0;
    size_t j = 0;  

    if (str[i] == '+' || str[i] == '-') {
        new_str[j++] = str[i++];  
    } else {
        new_str[j++] = '+';  
    }

    if (str[i] < '0' || str[i] > '9') {
        return 0;
    }
    new_str[j++] = str[i++];

    if (str[i] != '.') {
        return 0;
    }
    new_str[j++] = str[i++];

    while (str[i] >= '0' && str[i] <= '9') {
        new_str[j++] = str[i++];
    }

    if (str[i] != 'E' && str[i] != 'e') {
        return 0;
    }
    new_str[j++] = 'E';

    i++; 

    if (str[i] == '+' || str[i] == '-') {
        new_str[j++] = str[i++];
    } else {
        new_str[j++] = '+';
    }

    while (str[i] >= '0' && str[i] <= '9') {
        new_str[j++] = str[i++];
    }

    if (i != len) {
        return 0;
    }

    new_str[j] = '\0';

    return 1;
}

// Преобразование числа формата mE±K в 0.mE±K+1
int convert_single_digit_exp(char *str, char *new_double) {
    size_t i = 0;
    size_t j = 0;

    if (str[i] == '+' || str[i] == '-') {
        new_double[j++] = str[i++];
    } else {
        new_double[j++] = '+';
    }

    if (str[i] >= '0' && str[i] <= '9' && (str[i + 1] == 'e' || str[i + 1] == 'E')) {
        new_double[j++] = '0';
        new_double[j++] = '.';
        new_double[j++] = str[i];
        i += 2; 

        new_double[j++] = 'E'; 

        if (str[i] == '+' || str[i] == '-') {
            new_double[j++] = str[i++];
        } else {
            new_double[j++] = '+';
        }

        int exp_value = atoi(&str[i]);
        exp_value -= 1;

        char exp_str[10];
        snprintf(exp_str, sizeof(exp_str), "%d", exp_value);

        strcat(new_double, exp_str);

        return 1;
    }
    
    return 0;
}
// 9999999999999999999999999999999999999999
// 999999999999999999999999999999