// #include "multiply.h"
// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>

// void reverse_num(char *num)
// {
//     size_t len = strlen(num);
//     for (size_t i = 0; i < len / 2; i++)
//     {
//         char temp = num[i];
//         num[i] = num[len - i - 1];
//         num[len - i - 1] = temp;
//     }
// }

// void reverse_array(int *arr, size_t size)
// {
//     for (size_t i = 0; i < size / 2; i++)
//     {
//         int temp = arr[i];
//         arr[i] = arr[size - i - 1];
//         arr[size - i - 1] = temp;
//     }
// }


// // void print_matrix(int matrix[MAX_LEN_ROW][MAX_LEN_COLUMN], size_t rows, size_t cols)
// // {
// //     for (size_t i = 0; i < rows; i++)
// //     {
// //         for (size_t j = 0; j < cols; j++)
// //         {
// //             printf("%d ", matrix[i][j]);
// //         }
// //         printf("\n");
// //     }
// //     printf("\n");
// // }

// // Генерация матрицы для умножения числа с плавающей точкой и целого числа
// int matrix_generator(double_data *double_num, int_data *int_num, result_data *result_num)
// {
//     char upd_mantissa[MAX_LEN_MANTISSA] = {0};

//     for (size_t i = 2; i < strlen(double_num->mantissa); i++)
//         upd_mantissa[i - 2] = double_num->mantissa[i];

//     reverse_num(upd_mantissa);
//     reverse_num(int_num->int_value);
//     char reversed_int[MAX_LEN_INT + 1] = {0};
//     strcpy(reversed_int, int_num->int_value);

//     char sign_int = int_num->num_sign;
//     char sign_double = double_num->num_sign;

//     if ((sign_int == '-' && sign_double == '+') || (sign_int == '+' && sign_double == '-'))
//         result_num->num_sign = '-';
//     else
//         result_num->num_sign = '+';

//     size_t len_int = strlen(reversed_int);
//     size_t len_double = strlen(upd_mantissa);
//     size_t rows = len_double;
//     size_t cols = len_int + len_double - 1;

//     int matrix_of_mult[MAX_LEN_ROW][MAX_LEN_COLUMN] = {0};
    
//     for (size_t i = 0; i < rows; i++)
//     {
//         for (size_t j = 0; j < len_int; j++)
//         {
//             int digit_double = upd_mantissa[i] - '0'; 
//             int digit_int = reversed_int[j] - '0';
//             matrix_of_mult[i][i + j] += digit_double * digit_int;
//         }
//     }
//     // print_matrix(matrix_of_mult, rows, cols);

//     int evaluated_number[MAX_LEN_MANTISSA] = {0};
//     size_t len_result_arr = 0;
    
//     matrix_solver(matrix_of_mult, rows, cols, evaluated_number, &len_result_arr, double_num);
//     if (form_result(evaluated_number, len_result_arr, result_num, double_num, int_num))
//         return 3;
//     return 0;
// }

// void separate_digit(int digit, char *str)
// {
//     if (digit == 0)
//     {
//         strcpy(str, "0");
//         return;
//     }

//     size_t c = 0;
//     while (digit != 0)
//     {
//         str[c++] = (digit % 10) + '0';
//         digit /= 10;
//     }
//     str[c] = '\0';
//     reverse_num(str);
// }

// // Округление мантиссы
// void round_mantissa(int *result_mas, size_t *len_arr, double_data *double_num) {
//     if (*len_arr >= MAX_LEN_MANTISS_RESULT_REAL) {
//         size_t last_digit_pos = MAX_LEN_MANTISS_RESULT_REAL;

//         for (int i = last_digit_pos; i > 0; i--) {
//             if (result_mas[i] >= 5) {
//                 result_mas[i] = 0;
//                 if (result_mas[i - 1])
//                 {
//                     result_mas[i - 1]++;
//                 }
//                 else
//                     result_mas[i - 1] = 0;
//             }
//         }

//         if (result_mas[0] >= 10) {
//             result_mas[0] = result_mas[0] % 10 + result_mas[0] / 10;
//             (*len_arr) = MAX_LEN_MANTISS_RESULT_REAL;

//             int new_order = atoi(double_num->order) + 1;
//             char buf[100];
//             separate_digit(new_order, buf);
//             strcpy(double_num->order, buf);
//         } else { 
//             *len_arr = MAX_LEN_MANTISS_RESULT_REAL;
//         }
//     }
// }

// // Решение матрицы и вычисление результата
// void matrix_solver(int matrix[][MAX_LEN_COLUMN], size_t rows, size_t cols, int *result_mas, size_t *len_arr, double_data *double_num) {
//     int mas_of_sums[100] = {0};

//     for (size_t i = 0; i < cols; i++) {
//         for (size_t j = 0; j < rows; j++) {
//             mas_of_sums[i] += matrix[j][i];
//         }
//     }

//     size_t carry = 0;
//     for (size_t i = 0; i < cols; i++) {
//         int temp = mas_of_sums[i] + carry;
//         result_mas[i] = temp % 10;
//         carry = temp / 10;
//     }

//     size_t current_len = cols;
    

//     if (carry > 0 && current_len < 40) {
//         int new_order = 0;
//         if (double_num->exp_sign == '-')
//             new_order = -atoi(double_num->order);
//         else
//             new_order = atoi(double_num->order);
//         new_order++;
//         new_order = abs(new_order);
//         char buf[100];
//         separate_digit(new_order, buf);
//         strcpy(double_num->order, buf);
//     } 
//     while (carry > 0) {
//         if (current_len >= MAX_LEN_MANTISSA) {
//             result_mas[current_len - 1]++;
//             break;
//         }
//         result_mas[current_len] = carry % 10;
//         carry /= 10;
//         current_len++;
//     }

//     *len_arr = current_len;

//     reverse_array(result_mas, *len_arr);

//     round_mantissa(result_mas, len_arr, double_num);
// }

// // Формирование финального результата
// int form_result(int *result_mas, size_t len, result_data *result_num, double_data *double_num, int_data *int_num) {
//     char first_num[MAX_FIRST_NUM_LEN + 1] = {0};
//     separate_digit(result_mas[0], first_num);

//     result_num->mantissa[0] = '0';
//     result_num->mantissa[1] = '.';
//     result_num->mantissa[2] = '\0';  

//     strcat(result_num->mantissa, first_num);
//     size_t cur_size_result = strlen(result_num->mantissa);
//     size_t last_non_zero = len;

//     for (size_t i = len - 1; i > 0; i--) {
//         if (result_mas[i] == 0) {
//             last_non_zero--;
//         } else {
//             break;
//         }
//     }

//     for (size_t i = 1; i < last_non_zero; i++) {
//         result_num->mantissa[cur_size_result++] = result_mas[i] + '0';
//     }
    
//     result_num->mantissa[cur_size_result] = '\0';

//     int int_order = 0;
//     if (double_num->exp_sign == '-') {
//         int_order = -atoi(double_num->order);
//     } else {
//         int_order = atoi(double_num->order);
//     }

//     int int_len = strlen(int_num->int_value);
//     int new_order = int_order + int_len - 1;

//     // Исправление: увеличиваем порядок на число цифр в результате
//     // new_order += last_non_zero - 1;

//     if (new_order < 0) {
//         result_num->exp_sign = '-';
//         separate_digit(-new_order, result_num->order);
//     } else {
//         result_num->exp_sign = '+';
//         separate_digit(new_order, result_num->order);
//     }

//     printf("Final Result : %c%sE%c%s\n", result_num->num_sign, result_num->mantissa, result_num->exp_sign, result_num->order);

//     return 0;
// }
