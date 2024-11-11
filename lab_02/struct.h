#ifndef STRUCT_H
#define STRUCT_H

#include "definitions.h"

typedef struct keys_t
{
    int index;
    int rooms_quantity;
} keys_t;

typedef struct primary_t
{
    short trim;
} primary_t;

typedef struct secondary_t
{
    char build_year[MAX_LEN_YEAR + 1];
    int quantity_prev_owners;
    short is_pet;
} secondary_t;


typedef union choose_type_t
{
    primary_t prime;
    secondary_t second;
} choose_type_t;

typedef struct desc_t
{
    char type_room[MAX_LEN_TYPE_ROOM + 1];
    char address[MAX_LEN_ADDRESS + 1];
    float area;
    int rooms_quantity;
    float square_cost;
    choose_type_t type;
} desc_t;


#endif