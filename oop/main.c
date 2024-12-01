#include <stdio.h>

typedef struct interface 
{
    void (*input)(struct interface*);
    void (*print)(struct interface*);
    int value;
} interface_t;


void scan(interface_t* self) 
{
    if (scanf("%d", &self->value) != 1)
        return;
}

void print_one(interface_t* self) {
    printf("Realization One: %d\n", self->value);
}

void print_two(interface_t* self) {
    printf("Realization Two: %d\n", self->value);
}

interface_t realization_one = {
    .input = scan,
    .print = print_one,
    .value = 42
};

interface_t realization_two = {
    .input = scan,
    .print = print_two,
    .value = 100
};

int main() {
    int n = 0;
    realization_one.input(&realization_one);
    realization_one.input(&realization_two);
    realization_one.print(&realization_one);
    realization_two.print(&realization_two);

    realization_one.input(&realization_one);
    realization_one.input(&realization_two);
    realization_one.print(&realization_one);
    realization_two.print(&realization_two);

    return 0;
}
