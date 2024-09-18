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
    printf("jdlkndlkneslkf\n");
    if (str[i] == '+' || str[i] == '-') {
        new_double[j++] = str[i++];
    } else {
        new_double[j++] = '+';
    }

    char *e_ptr = strchr(str, 'e');
    size_t e_pos = (size_t)(e_ptr - str);
    // int e_i = e_pos + 1;
    // int e_t = 0;
    // char old_order[10];
    // while (str[e_i] != '\0' && str[e_i] != '\n')
    // {
    //     old_order[e_t++] = str[e_i++];
    // }
    // int old_int_order = atoi(old_order);

    if (str[i] >= '0' && str[i] <= '9' && e_ptr) {

        if ((str[i + 2] != '+' && str[i + 2] != '-') && !isdigit(str[i + 2]))
        {
            printf("fault_here - %c\n", str[i + 2]);
            return 0;
        }
        new_double[j++] = '0';
        new_double[j++] = '.';
        int diff_order = 0;
        while (i < e_pos)
        {
            new_double[j++] = str[i++];
            diff_order++;
        }
        
        new_double[j++] = 'E'; 

        if (str[i] == '+' || str[i] == '-') {
            new_double[j++] = str[i++];
        } else {
            new_double[j++] = '+';
        }
        printf("before exp : %s\n", new_double);
        char temp_order[10];
        int c = 0;
        i += 1;
        while (str[i] != '\0' && str[i] != '\n')
        {
            temp_order[c++] = str[i++];
        }
        if (strlen(temp_order) > 5)
            return 0;
        int exp_value = atoi(temp_order);
        exp_value += diff_order;
        // exp_value += old_int_order;
        printf("diff : %d, exp : %d\n", diff_order, atoi(temp_order));
        e_ptr = strchr(new_double, 'E');
        e_pos = (size_t)(e_ptr - new_double);
        if (exp_value < 0)
            new_double[e_pos + 1] = '-';
        else
            new_double[e_pos + 1] = '+';

        char exp_str[10];
        snprintf(exp_str, sizeof(exp_str), "%d", abs(exp_value));

        strcat(new_double, exp_str);
        

        return 1;
    }
    
    return 0;
}
// 9999999999999999999999999999999999999999
// 999999999999999999999999999999