#ifndef STRUCTS_H
#define STRUCTS_H



typedef struct node_t
{
    char *value;
    struct node_t *left;
    struct node_t *right;
} node_t;



#endif