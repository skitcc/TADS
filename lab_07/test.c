#include <stdio.h>
#include <string.h>
#include <stdlib.h>


static int hash(const char *str, int size) 
{
    unsigned int hash_value = 0;
    const unsigned int prime = 53;

    for (size_t i = 0; i < strlen(str); i++) 
        hash_value = (hash_value * prime + (unsigned char)str[i]);

    hash_value %= size;

    return (int)hash_value;
}


int main(void)
{
    char str[10];

    for (int i = 0; i < 100; i++)
    {
        // sprintf(str, "%d", i);
        str[0] = rand();
        str[1] = rand();
        str[2] = rand();
        str[3] = rand();
        str[4] = rand();
        str[5] = rand();
        str[6] = 0;
        printf("%s\n", str, hash(str, 103));
    }
    return 0;
}