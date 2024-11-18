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


#define LEN_FILENAME 50
#define MAX_MEASURMENTS 1000


#define PRINT_COLOR(color, message) printf(color message RESET "\n")


#endif