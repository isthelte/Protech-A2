#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

struct stack * create_stack(int length) {
    struct stack * s = malloc(sizeof(struct stack));
    s->top = -1;
    s->length = length;
    s->data = malloc(sizeof(double)*length);
    
    return s;
}

void free_stack(struct stack *s) {
    free(s->data);
    free(s);
}

void push(struct stack *s, double value) {
    if (s->top == s->length-1) {
        resize(s, (int)s->length*RESIZE_FACTOR);
    }
    
    s->top++;
    s->data[s->top] = value;
}

double peek(struct stack *s) {
    return s->data[s->top];
}

double pop(struct stack *s) {
    s->top--;
    return s->data[s->top+1];
}

void resize(struct stack *s, int new_length) {
    double *old_data = s->data;
    //printf("in resize %i, %i\n", s->length, new_length);
    s->data = malloc(sizeof(double)*new_length);
    for (int i = 0; i <= s->top; i++) {
        s->data[i] = old_data[i];
    }
    
    s->length = new_length;
    free(old_data);
}

void print_stack(struct stack *s) {
    printf("%i/%i: ", s->top, s->length);
    for (int i = 0; i <= s->top; i++) {
        printf("%lf ", s->data[i]);
    }
    printf("\n");
}
