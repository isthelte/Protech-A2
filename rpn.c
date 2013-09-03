#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "rpn.h"
#include "stack.h"
#include "operators.h"
#include "variables_mapping.h"

//Create a table to alllocate variables to its values
struct table * var_List;

void rpn_createVarList(){
    var_List = createTable();
}

int rpn_find_var_index(char * name){
    return find_variable(var_List, name);
}

double rpn_get_var_value(int index){
    //printf("Name is %s\n", name );
    return get_variable(var_List, index);
}

//This method will evaluate the expression in RPN and return the result
double rpn_eval(char *exp, char * *invalidVar, char * *invalidAssignment) {
    // create a stack based on the length of the expression
    // this is just a guess of the space we are going to need
    // the stack will automatically increase its size if necessary
    int exp_length = strlen(exp);
    struct stack *s = create_stack(exp_length/2);
    char *token, *copy;
    double value, left, right;
    
    // we need to make a copy of the expression to not "destroy" it while
    // we parse it
    printf("Got here\n");
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
            
            //Check to see if what we get is an '=' sign or an operator
            if (find_operation(token) != -1){
                //If it is a mere operator, carry on and do as usual

                // pop the right operand
                struct element * rightEl = pop(s);

                //Make a decision: If it is a number, then just assign the value to right
                //If it is not, try looking for the variable with that name, and return its value to right
                if (rightEl->type == ELEMENT_NUMBER){

                    right =  rightEl->number;

                } else {
                    int var_index = rpn_find_var_index(rightEl->op);

                    //We can only evaluate the expression if the variable really exists
                    if (var_index != -1){
                        right = rpn_get_var_value(var_index);
                    } else {

                        //If it does not exist, terminate the evaluation an send a signal
                        //That the expression is invalid through the char * invalid Var
                        free(copy);
                        free_stack(s);
                                    
                        strcpy(*invalidVar, rightEl->op);
                        //Again, make sure nothing weird happen here
                        (*invalidVar)[strlen(rightEl->op)] = '\0';
                        return -1;
                    }
                }

                //pop the left operand 
                //UPDATE: THE LEFT OPERAND MUST BE A VARIABLE!
                struct element * leftEl = pop(s);

                //Make a decision: If it is a number, then continue and take the value
                //If it is not, try looking for the variable with that name, and assign right to it
                if (leftEl->type == ELEMENT_NUMBER){

                    left = leftEl->number;

                } else {

                    char * variable = leftEl->op;

                    //Continue to check if the variable name is valid or not
                    //If it contains any number from 0 to 9 at the beginning, it is not valid
                    for (int i = 0; i < 10; ++i)
                    {
                        if (variable[0] == i){

                            free(copy);
                            free_stack(s);

                            strcpy(*invalidAssignment, "A variable name cannot start with a number");
                            return -1;
                        }
                    }

                    int var_index = rpn_find_var_index(variable);
                    
                    if (var_index != -1){
                        //We can only evaluate the expression if the variable really exists
                        left = rpn_get_var_value(var_index);
                    } else {

                        free(copy);
                        free_stack(s);

                        //If it is not there, terminate the operation and throw an error
                        strcpy(*invalidVar, variable);
                        (*invalidVar)[strlen(variable)] = '\0';                        
                        return -1;
                    }

                }

                value = execute_operation(token, left, right);
                // push the result back on the stack
                push(s, create_node_number(value));                

            } else if (token[0] == '=') { //If it is an '=' sign

                // pop the right operand
                struct element * rightEl = pop(s);

                //Make a decision: If it is a number, then just assign the value to right
                //If it is not, try looking for the variable with that name, and return its value to right
                if (rightEl->type == ELEMENT_NUMBER){
                    right =  rightEl->number;
                } else {
                    int var_index = rpn_find_var_index(rightEl->op);

                    //We can only evaluate the expression if the variable really exists
                    if (var_index != -1){
                        right = rpn_get_var_value(var_index);
                    } else {
                        //If it does not exist, terminate the evaluation an send a signal
                        //That the expression is invalid through the char * invalid Var
                        free(copy);
                        free_stack(s);
                            
                        strcpy(*invalidVar, rightEl->op);
                        //Again, make sure nothing weird happen here
                        (*invalidVar)[strlen(rightEl->op)] = '\0';
                        return -1;
                    }
                }                

                //pop the left operand 
                //UPDATE: THE LEFT OPERAND MUST BE A VARIABLE!
                struct element * leftEl = pop(s);

                //Make a decision: If it is a number, then terminate the evaluation
                //If it is not, try looking for the variable with that name, and assign right to it
                if (leftEl->type == ELEMENT_NUMBER){

                    free(copy);
                    free_stack(s);

                    strcpy(*invalidAssignment, "Left side of the '=' sign is not a valid variable");
                    return -1;
                } else { //If it is not a number, then there is hope

                    char * variable_found = leftEl->op;    

                    //Continue to check if the variable name is valid or not
                    //If it contains any number from 0 to 9 at the beginning, it is not valid
                    for (int i = 0; i < 10; ++i)
                    {
                        if (variable_found[0] == i){

                            free(copy);
                            free_stack(s);

                            strcpy(*invalidAssignment, "A variable name cannot start with a number");
                            return -1;
                        }
                    }

                    //If it is valid, continue~
                    //printf("Got here\n");
                    int var_index = rpn_find_var_index(variable_found);
                    
                    if (var_index != -1){
                        //If it is already there, simply edit the variable
                        edit_variable(var_List, var_index, right);
                    } else {
                        //If it is not there yet, create a new variable and assign right to it
                        add_variable(var_List, variable_found, right);
                    }
                }

                //value will be the result, thus the right
                value = right;
                // push the result back on the stack
                push(s, create_node_number(value));

            } else { //If it is not an operator, nor an '=' sign, then it must be a variable

                // push the variable back on the stack
                push(s, create_node_operator(token));

            }

            
        }

        //print_stack(s);
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
