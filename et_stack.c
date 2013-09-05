#include <stdlib.h>
#include <stdio.h>

#include "et_stack.h"

struct et_stack * ets_create_stack(int length){
	struct et_stack * ets = malloc(sizeof(struct et_stack));

	ets->top = -1;
	ets->length = length;
	ets->data = malloc(sizeof(struct et_node *)*length);
}

void ets_free_stack(struct et_stack *s){
	free(s->data);
	free(s);
}

void ets_push(struct et_stack *s, struct et_node *node){
	if (s->top == s->length-1) {
        resize(s, (int)s->length*ETS_RESIZE_FACTOR);
    }
    
    s->top++;
    s->data[s->top] = node;
}

struct et_node * ets_peek(struct et_stack *s){
    return s->data[s->top];
}

struct et_node * ets_pop(struct et_stack *s){
    s->top--;
    return s->data[s->top+1];
}

void ets_resize(struct et_stack *s, int new_length){
	struct et_node ** old_data = s->data;
    //printf("in resize %i, %i\n", s->length, new_length);
    s->data = malloc(sizeof(struct et_node)*new_length);
    for (int i = 0; i <= s->top; i++) {
        s->data[i] = old_data[i];
    }
    
    s->length = new_length;
    free(old_data);
}

void ets_print_stack(struct et_stack *s){}