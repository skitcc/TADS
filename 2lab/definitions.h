#ifndef DEFINITIONS_H
#define DEFINITIONS_H



#define RED "\033[31m"
#define GREEN  "\x1B[32m"
#define RESET "\033[0m"

#define GHZ 3700000000

#define MAX_LEN_STRUCTURES 1000
#define MAX_SIZE_ARRAY 1000

#define MAX_LEN_ADDRESS 25
#define MAX_LEN_YEAR 10
#define MAX_LEN_FILENAME 100
#define MAX_LEN_SIDE_FIELDS 10
#define MAX_LEN_TYPE_ROOM 10

//Errors

#define ERROR_READING_TYPE_ROOM 1
#define ERROR_READING_ADDRESS 2
#define ERROR_READING_SQUARE 3
#define ERROR_READING_AMOUNT_ROOMS 4
#define ERROR_READING_COST 5
#define ERROR_READING_TRIM 6
#define ERROR_READING_YEAR 7
#define ERROR_READING_LAST_OWNERS 8
#define ERROR_READING_PETS 9
#define ERROR_VALUE_PETS 10
#define ERROR_MATCHING_REG_EXPR 11
#define ERROR_READING_FILENAME 12
#define ERROR_OPENING_FILE 13
#define ERROR_READING_AMOUNT_OF_STRUCTS 14
#define ERROR_INCORRECT_AMOUNT_SCRUCTS 15
#define ERROR_EXCESS_STRUCTS 16
#define ERROR_READING_STRUCT 17






#endif