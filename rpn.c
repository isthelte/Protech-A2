#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rpn.h"
#include "stack.h"
#include "operators.h"

//This method will evaluate the expression in RPN and return the result
double rpn_eval(char *exp) {
    // create a stack based on the length of the expression
    // this is just a guess of the space we are going to need
    // the stack will automatically increase its size if necessary
    int exp_length = strlen(exp);
    struct stack *s = create_stack(exp_length/2);
    char *token, *copy;
    double value, left, right;
    
    // we need to make a copy of the expression to not "destroy" it while
    // we parse it
    copy = malloc(sizeof(char)*exp_length);
    strcpy(copy, exp);

    // tokenise the copy of the expression based on space characters
    token = strtok(copy, " ");
    // while there is another token to process
    while (token != NULL) {
        //printf("%s", token);
        //printf("(%i)\n", strlen(token));
        // sscanf is like scanf, but works on strings instead of stdin
        // if the token is a double       
        if (0.00 < sscanf(token, "%lf", &value)) {
            //printf("number: %s\n", token);
            // push the double on the stack            
            push(s, create_node_number(value));
        } else {
            // the token is not a double, therefore it must be an operator (hopefully)
            //printf("operator: %s\n", token);
            // pop the right and left operands
            right = pop(s)->number;
            left = pop(s)->number;
            // evaluate the operator on left and right
            //printf("operator: %s\n", token);
            //value = operations[find_operation(token)](left,right);
            value = execute_operation(token, left, right);
            // push the result back on the stack
            push(s, create_node_number(value));            
        }

        // get the next token
        // strtok has a state: when called with NULL as the first argument,
        // it will continue to tokenise the previous string given to it
        token = strtok(NULL, " ");           
        //print_stack(s);
    }    
    
    value = pop(s)->number;

    free(copy);
    free_stack(s);

    return value;
}
