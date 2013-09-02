#ifndef STACK
#define STACK

#define RESIZE_FACTOR 1.5

enum element_type {ELEMENT_NUMBER, ELEMENT_OPERATOR};

struct element {
    enum element_type type;              
    union {
        double number;      /**< the number to store in the node */
        char op[50];         /**< an operator has at most 2 chars. UPDATE: Set to 50 char to include variable name */
    };
};

struct stack {
    int top;
    int length;
    struct element ** data;
};

struct element * create_node_number(double value);

struct element * create_node_operator(char * value);

struct stack * create_stack(int length);

void free_stack(struct stack *s);

void push(struct stack *s, struct element * e);

struct element *peek(struct stack *s);

struct element *pop(struct stack *s);

void resize(struct stack *s, int new_length);

void print_stack(struct stack *s);
#endif
