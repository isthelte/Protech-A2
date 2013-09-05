#ifndef STACK
#define STACK

#define RESIZE_FACTOR 1.5

/**
 * There are only 2 types of a stack's element: number, or operator (which also include variable names)
 */
enum element_type {ELEMENT_NUMBER, ELEMENT_OPERATOR};

/**
 * Stack node struct.
 */
struct element {
    enum element_type type; /**< the enum to determine the type of the element */             
    union {
        double number;      /**< the number to store in the node */
        char op[50];         /**< an operator has at most 2 chars, but it is set to 50 char to include variable names */
    };
};

/**
 * Stack struct.
 */
struct stack {
    int top;					/**< the top of the stack at the moment */
    int length;					/**< the maximum size of the stack */
    struct element ** data;		/**< an array of pointers to the elements in the stack */
};

/**
 * Create a node of type element to hold a number (double)
 * This function also returns the pointer to that node.
 * @param value the value of the number in the node.
 * @return the pointer to the node.
 */
struct element * create_node_number(double value);

/**
 * Create a node of type element to hold an operator (char *)
 * This function also returns the pointer to that node.
 * @param value the operator in the node.
 * @return the pointer to the node.
 */
struct element * create_node_operator(char * value);

/**
 * Create a stack of the SIZE given
 * This function also returns the pointer to that stack.
 * @param length the SIZE of the stack.
 * @return the pointer to the stack.
 */
struct stack * create_stack(int length);

/**
 * Free the stack and all of its data
 * @param s the pointer to the stack to be freed.
 */
void free_stack(struct stack *s);

/**
 * Push an element onto the top of the stack
 * @param s the pointer to the stack to push the element on.
 * @param e the pointer to the element to be pushed on the stack.
 */
void push(struct stack *s, struct element * e);

/**
 * Peek: Get the top element on the stack without taking it out
 * @param s the pointer to the stack to peek.
 * @return the pointer to the element at the top of the stack.
 */
struct element *peek(struct stack *s);

/**
 * Pop: Get the top element on the stack and take it out of the stack
 * @param s the pointer to the stack to pop.
 * @return the pointer to the element at the top of the stack.
 */
struct element *pop(struct stack *s);

/**
 * Resize the stack to increase its size
 * @param s the pointer to the stack to change size.
 * @param new_length the new size of the stack.
 */
void resize(struct stack *s, int new_length);

/**
 * Print out all the elements inside the stack.
 * Note: This will not take out (pop) any element in the stack
 * @param s the pointer to the stack to change size.
 */
void print_stack(struct stack *s);
#endif
