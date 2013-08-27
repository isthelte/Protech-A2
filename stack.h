#ifndef STACK
#define STACK

#define RESIZE_FACTOR 1.5

struct stack {
    int top;
    int length;
    double *data;
};

struct stack * create_stack(int length);

void free_stack(struct stack *s);

void push(struct stack *s, double value);

double peek(struct stack *s);

double pop(struct stack *s);

void resize(struct stack *s, int new_length);

void print_stack(struct stack *s);
#endif
