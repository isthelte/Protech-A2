#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"


struct element * create_node_number(double value){
    struct element * e = malloc(sizeof(struct element));
    e->type = ELEMENT_NUMBER;
    e->number = value;

    return e;
}

struct element * create_node_operator(char * value){
    struct element * e = malloc(sizeof(struct element));
    e->type = ELEMENT_OPERATOR;
    e->op[0] = value[0];
    if (strlen(value) == 2)
        e->op[1] = value[1];
    if (strlen(value) > 2){        
        for (int i = 0; i < strlen(value); ++i)
        {            
            e->op[i] = value[i];
        }
    }

    //Make sure nothing "strange" comes after that
    e->op[strlen(value)] = '\0';

    return e;    
}

struct stack * create_stack(int length) {
    
    struct stack * s = malloc(sizeof(struct stack));
    s->top = -1;
    s->length = length;
    s->data = malloc(sizeof(struct element *)*length);
    
    return s;
}

void free_stack(struct stack *s) {        

    free(s->data);

    free(s);
}

void push(struct stack *s, struct element * e) {
    if (s->top == s->length-1) {
        resize(s, (int)s->length*RESIZE_FACTOR);
    }
    
    s->top++;
    s->data[s->top] = e;
}

struct element * peek(struct stack *s) {
    
    //There is no data left to pop
    if (s->top == -1){
        return NULL;
    }

    return s->data[s->top];
}

struct element * pop(struct stack *s) {

    //There is no data left to pop
    if (s->top == -1){
        return NULL;
    }

    s->top--;    
    return s->data[s->top+1];
}

void resize(struct stack *s, int new_length) {
    struct element ** old_data = s->data;
    //printf("in resize %i, %i\n", s->length, new_length);
    s->data = malloc(sizeof(struct element)*new_length);
    for (int i = 0; i <= s->top; i++) {
        s->data[i] = old_data[i];
    }
    
    s->length = new_length;
    free(old_data);
}

void print_stack(struct stack *s) {
    printf("%i/%i: ", s->top, s->length);
    for (int i = 0; i <= s->top; i++) {
        if (s->data[i]->type == ELEMENT_NUMBER){
            printf("%lf ", s->data[i]->number);    
        } else {
            printf("%s ", s->data[i]->op);
        }    
    }
    printf("\n");
}
