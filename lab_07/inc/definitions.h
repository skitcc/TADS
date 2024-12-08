#ifndef DEFINITIONS_H
#define DEFINITIONS_H


#define RESET "\033[0m"
#define BLACK "\033[0;m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define VIOLET "\033[0;35m"
#define TURQ "\033[0;36m"
#define WHITE "\033[0;37m"


#define BUILD_TREE 1
#define INSERT 2
#define DELETE 3
#define SEARCH 4
#define VISUALISE 5
#define BUILD_HT 6
#define ADD_HT 7
#define DELETE_HT 8
#define SEARCH_HT 9
#define MEASURMENTS 10
#define PRINT_HTS 11

#define LEN_FILENAME 100
#define MAX_MEASURMENTS 1000
#define MAX_LEN_FILE 10000


#define PRINT_COLOR(color, message) printf(color message RESET "\n")


#endif