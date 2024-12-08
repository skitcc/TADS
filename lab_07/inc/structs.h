#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdbool.h>

#define MAX_WORD_LENGTH 100

typedef struct bst
{
    char *value;
    struct bst *left;
    struct bst *right;
} bst_t;


typedef struct avl
{
    char *value;
    int height;
    struct avl *left;
    struct avl *right;
} avl_t;

typedef struct hash_node 
{
    char word[MAX_WORD_LENGTH];
    struct hash_node *next;
} hash_node_t;

typedef struct opened
{
    int size;
    char** open_table;
    int* status;
    int comparisons;
    int count;
} open_ht;

typedef struct closed
{
    int size;
    hash_node_t **closed_table;
    int comparisons;
} closed_ht;



struct tree_interface
{
    void *root;
    void *(*init)(const char *filename);
    void *(*insert)(void *root, const char *value);
    void *(*delete)(void *node, char value, int *comparisons);
    void *(*search)(void *node, const char *value, int *comparisons);
    avl_t *(*balance)(bst_t *root);
    void (*vusualise)(void *head, const char *filename, bool is_bst);
    void (*destroy)(void *head);
};


struct ht_interface
{
    void *root;
    void *(*init)(int size);
    void (*insert)(void *root, const char *word);
    void *(*search)(void *root, const char *word);
    void (*delete)(void *root, const char *word);
    void (*destroy)(void *root);
    void (*print)(void *root);
    void (*print_comps)(void *root);
};


#endif