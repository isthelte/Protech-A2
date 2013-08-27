#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rpn.h"
#include "stack.h"

//Introduce the methods for the operations

double add(double a, double b){
    return a+b;
}

double minus(double a, double b){
    return a-b;
}

double multiply(double a, double b){
    return a*b;
}

double divide(double a, double b){
    return a/b;
}

double power(double a, double b){    
    //If b = 0, then there is no need to calculate
    if (b == 0){
        return 1;
    } else {
        double result = a;
        double absB = (b > 0) ? b : b * (-1);

        for (int i = 1; i < absB; ++i)
        {
            result *= a;
        }

        return (b > 0) ? result : 1 / result;
    }    
}

double maximum(double a, double b){
    return (a >=  b) ? a : b;
}

double minimum(double a, double b){
    return (a <= b) ? a : b;
}

double distance(double a, double b){
    return (a - b > 0) ? (a - b) : (-1) * (a - b);
}

//Make 2 arrays: 1 for pointers and 1 for operation symbols
double (* operations[])(double, double) = {add, minus, multiply, divide, maximum, minimum, distance, power};
char * op_symbols[] = {"+", "-", "*", "/", "#", "_", "||", "**"};

int find_operation(char * operator){    

    int length = strlen(operator);

    //Check to see if the string is valid
    if (length == 2){
        //printf("%s\n", "found length 2");
        //13 is the ascii code of CR (Carriage Return)        
        //10 is the ascii code of \n (new line)
        if (operator[1]  == 13 || operator[1] == 10){
            //Eliminate these character to assume a good strcmp 
            operator[1] = '\0';
            //printf("%s %s(%i)\n", "fixed into ", operator, strlen(operator));
        }

    } else if (length == 3){
        //13 is the ascii code of CR (Carriage Return)        
        //10 is the ascii code of \n (new line)
        if (operator[2]  == 13 || operator[2] == 10){
            //Eliminate these character to assume a good strcmp 
            operator[2] = '\0';
        }
    }

   for (int i = 0; i < 8; i += 1)
   {
        if (strcmp(operator, op_symbols[i]) == 0){
        //if (operator[0] == op_symbols[i][0]){               
           return i; 
        }
    }   

   
    return -1; 

}

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
        // if the token is an int       
        if (0.00 < sscanf(token, "%lf", &value)) {
            //printf("number: %s\n", token);
            // push the int on the stack
            push(s, value);
        } else {
            // the token is not an int, therefore it must be an operator (hopefully)
            //printf("operator: %s\n", token);
            // pop the right and left operands
            right = pop(s);
            left = pop(s);
            // evaluate the operator on left and right
            //printf("operator: %s\n", token);
            value = operations[find_operation(token)](left,right);
            // push the result back on the stack
            push(s, value);            
        }

        // get the next token
        // strtok has a state: when called with NULL as the first argument,
        // it will continue to tokenise the previous string given to it
        token = strtok(NULL, " ");           
        //print_stack(s);
    }    
    
    value = pop(s);

    free(copy);
    free_stack(s);

    return value;
}
