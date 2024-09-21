#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse_double.h"

// Вставка символа в начало строки
void char_insertion(char *str, size_t len, char to_insert) {
    for (size_t i = len; i > 0; i--) {
        str[i] = str[i - 1];
    }
    str[0] = to_insert;
}

// Перемещение символа в начало строки
void move_char_start(char *str, size_t pos) {
    for (size_t i = pos; i > 0; i--) {
        char temp = str[i - 1];
        str[i - 1] = str[i];
        str[i] = temp;
    }
}

// Проверка на допустимые символы до экспоненты
int before_exp_check(char *str, size_t pos, size_t start) {
    size_t i = start + 1;    
    while (i < pos) {
        if (str[i] < '0' || str[i] > '9') {
            return 1;
        }
        i++;
    }
    return 0;
}

// Проверка на допустимые символы после экспоненты
int after_exp_check(char *str, size_t pos, size_t len) {
    if (str[pos] != 'E' && str[pos + 1] != '+' && str[pos + 1] != '-') {
        return 1;
    }
    for (size_t i = pos + 2; i < len; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 3;
        }
    }
    return 0;
}

// Проверка правильности записи вещественного числа
int valid_double(char *str, size_t dot_pos, size_t e_pos, size_t len) {

    for (size_t i = 0; i < len; i++) {
        if (str[i] == '.' && i != dot_pos) {
            return 1;
        }
        if ((str[i] == 'E' || str[i] == 'e') && e_pos != i) {
            return 2;
        }
    }
    return 0;
}

// Инверсия строки
void reverse(char *str, size_t len) {
    for (size_t i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Преобразование целого числа в строку
void int_to_char(char *str, int num) {
    size_t i = 0;
    if (num == 0) {
        str[i++] = '0';
    } else {
        while (num > 0) {
            str[i++] = (num % 10) + '0';
            num /= 10;
        }
    }
    str[i] = '\0';  
    reverse(str, i);  
}

// Проверка мантиссы и преобразование числа в правильный формат
int mantissa_check(char *double_num, char *new_double) {
    size_t len = strlen(double_num);
    size_t order = 0;




    if (double_num[0] == '\0') {
        printf("Вещественное число пустое\n");
        return 3;
    }


    char *dot_p1 = strchr(double_num, '.');
    char *e_p1 = (strchr(double_num, 'E') != NULL) ? strchr(double_num, 'E') : strchr(double_num, 'e');

    if (e_p1 && dot_p1) {
        is_valid_scientific_notation(double_num, new_double);
        return 0;
    }

    if (e_p1 && !dot_p1) {
        int rm = convert_single_digit_exp(double_num, new_double);
        printf("rm parse : %d\n", rm);
        if (!rm)
            return 2;
        return 0;
    }

    if (double_num[0] == '.') {
        char_insertion(double_num, len, '0');
        len++;
    }


    if (double_num[0] >= '0' && double_num[0] <= '9' && dot_p1 != NULL) {
        printf("here\n");

        char *p1 = dot_p1;
        size_t dot_pos = (size_t)(p1 - double_num);

        if (dot_pos == 1 && double_num[0] == '0')
            order = 0;

        else
        {
            size_t temp_order = dot_pos;
            move_char_start(double_num, dot_pos);
            char_insertion(double_num, ++len, '0');
            order = temp_order;
        }


        
    }

    if ((isdigit(double_num[0]) || (double_num[0] == '-' || double_num[0] == '+')) && dot_p1 == NULL) {
        size_t first_non_zero = 0;
        // printf("here\n");
        char sign = '+';
        if (isdigit(double_num[0]) || double_num[0] == '+')
            sign = '+';
        else
            sign = '-';
        if (double_num[0] == '+' || double_num[0] == '-')
        {
            for (size_t i = 0; i < len - 1; i++)
            {
                char temp = double_num[i + 1];
                double_num[i + 1] = double_num[i];
                double_num[i] = temp;
            }
            len--;
        }
        
        while (double_num[first_non_zero] == '0' && first_non_zero < len - 1) {
            first_non_zero++;
        }

        if (first_non_zero > 0) {
            for (size_t i = 0; i <= len - first_non_zero; i++) {
                double_num[i] = double_num[i + first_non_zero];
            }
            len -= first_non_zero;
        }
        char_insertion(double_num, len, '.');
        char_insertion(double_num, len + 1, '0');
        char_insertion(double_num, len + 2, sign);
        len += 3;
        order = len - 3;
    }
    printf("my_double : %s\n", double_num);


    char *dot_ptr = strchr(double_num, '.');
    char *e_ptr = (strchr(double_num, 'E') != NULL) ? strchr(double_num, 'E') : strchr(double_num, 'e');
    
    size_t dot_pos = (dot_ptr != NULL) ? (size_t)(dot_ptr - double_num) : len;
    size_t e_pos = (e_ptr != NULL) ? (size_t)(e_ptr - double_num) : len;

    double_num[len] = '\0';

    char old_order[10] = {0};
    if (e_ptr != NULL && (len - e_pos - 1) > 0) {        
        for (size_t i = e_pos + 1; i < len; i++) {
            old_order[i - e_pos - 1] = double_num[i];
        }
        old_order[len - e_pos - 1] = '\0';
    }


    if (e_ptr == NULL) {
        double_num[len] = 'E';
        e_pos = len;
        double_num[++len] = '+';
        double_num[++len] = '\0';
        char buf[100];
        int_to_char(buf, order);
        strcat(double_num, buf);
        len += strlen(buf);
    }

    int old_int_order = atoi(old_order);
    int new_order = old_int_order + (int)order;
    char new_order_str[10];
    snprintf(new_order_str, sizeof(new_order_str), "%d", new_order);
    if (strlen(new_order_str) > 5) {
        return 5;
    }


    size_t c = 1;
    size_t start = 0;
    if (double_num[0] != '+' && double_num[0] != '-') {
        new_double[0] = '+';
        start = 0;
    } else if (double_num[0] == '+') {
        new_double[0] = '+';
        start = 1;
    } else if (double_num[0] == '-') {
        new_double[0] = '-';
        start = 1;
    }

    
   
    for (size_t i = start; i < dot_pos; i++) {
        // printf("%d\n", double_num[i]);
        // if (double_num[i] != '.' || !isdigit(double_num[i]))
        // {
        //     printf("Ошибка, встречен неопознанный символ -  %c\n", double_num[i]);
        //     return 2;
        // }
        new_double[c++] = double_num[i];
    }

    for (size_t i = dot_pos; i < e_pos; i++) {
        printf("%d\n", double_num[i]);
        // if (double_num[i] != 'E' || double_num[i] != '.' || !isdigit(double_num[i]))
        // {
        //     printf("Ошибка, встречен неопознанный символ -  %c\n", double_num[i]);
        //     return 2;
        // }
        new_double[c++] = double_num[i];
    }
    new_double[c++] = 'E';

    if (new_order >= 0) {
        new_double[c++] = '+';
    }


        
    strcat(new_double, new_order_str);

    // new_double[c + strlen(new_order_str) - 1] = '\0';

    char *dot_p2 = strchr(new_double, '.');
    char *e_p2 = (strchr(new_double, 'E') != NULL) ? strchr(new_double, 'E') : strchr(new_double, 'e');
    
    size_t dot_po2 = (dot_p2 != NULL) ? (size_t)(dot_p2 - new_double) : c;
    size_t e_po2 = (e_p2 != NULL) ? (size_t)(e_p2 - new_double) : c;


    printf("dot_po2 : %zu , e_po2 : %zu\n",dot_po2, e_po2);

    if (valid_double(new_double, dot_po2, e_po2, c))
    {
        printf("Ошибка в вещ числе!\n");
        return 2;
    }

    if (before_exp_check(new_double, e_po2, dot_po2))
    {
        printf("Ошибка в вещ числе!\n");
        return 2;   
    }

    if (after_exp_check(new_double, e_po2, c))
    {
        printf("Ошибка в вещ числе!\n");
        return 2;  
    }

    
    return 0;
}