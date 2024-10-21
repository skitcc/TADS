#include "read.h"


int read_expr(char *expr)
{
    printf(TURQ "\nВведите выражение, содержащее скобки, без пробелов "
                "(не более 10000 символов):\n" RESET);
    if (fgets(expr, MAX_LEN_EXPR + 2, stdin) == NULL)
    {
        printf("%sОшибка ввода выражения!%s\n", RED, RESET);
        return ERR_INPUT;
    }

    if (strlen(expr) > MAX_LEN_EXPR)
    {
        printf("%sВведенное выражение больше указанной длины!%s\n", RED, RESET);
        return ERR_OVERFLOW;
    }

    expr[strlen(expr) - 1] = '\0';
    printf("%sВыражение успешно считано!%s\n", GREEN, RESET);

    return EXIT_SUCCESS;

}