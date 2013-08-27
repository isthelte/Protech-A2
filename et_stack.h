#ifndef STACK
#define STACK

#define RESIZE_FACTOR 1.5
#include "exp_tree.h"

struct et_stack {
    int top;
    int length;
    struct et_node **data;
};

struct et_stack * create_stack(int length);

void free_stack(struct et_stack *s);

void push(struct et_stack *s, struct et_node *node);

struct et_node * peek(struct et_stack *s);

struct et_node * pop(struct et_stack *s);

void resize(struct et_stack *s, int new_length);

void print_stack(struct et_stack *s);
#endif
