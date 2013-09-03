#ifndef ET_STACK
#define ET_STACK

#define RESIZE_FACTOR 1.5
#include "exp_tree.h"

struct et_stack {
    int top;
    int length;
    struct et_node **data;
};

struct et_stack * ets_create_stack(int length);

void ets_free_stack(struct et_stack *s);

void ets_push(struct et_stack *s, struct et_node *node);

struct et_node * ets_peek(struct et_stack *s);

struct et_node * ets_pop(struct et_stack *s);

void ets_resize(struct et_stack *s, int new_length);

void ets_print_stack(struct et_stack *s);
#endif
