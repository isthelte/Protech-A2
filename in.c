#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "in.h"
#include "stack.h"
#include "operators.h"
#include "variables_mapping.h"

//Create a table to alllocate variables to its values
struct table * var_List;

void createVarList(){
    var_List = createTable();
}

int find_var_index(char * name){
    return find_variable(var_List, name);
}

double get_var_value(int index){
    //printf("Name is %s\n", name );
    return get_variable(var_List, index);
} 

//This method will evaluate the expression in RPN and return the result
double in_eval(char *exp, char ** invalidVar) {
    // create a stack based on the length of the expression
    // this is just a guess of the space we are going to need
    // the stack will automatically increase its size if necessary
    int exp_length = strlen(exp);
    struct stack *s = create_stack(exp_length/2);

    //create necessary values for storing operators and operands
    char *token, *copy, *operator_found, *variable_found;
    double value, left, right;
    
    // we need to make a copy of the expression to not "destroy" it while
    // we parse it
    copy = malloc(sizeof(char)*exp_length);
    strcpy(copy, exp);

    // tokenise the copy of the expression based on space characters
    token = strtok(copy, " ");
    // while there is another token to process
    while (token != NULL) {        

        //Make sure there is only the character ) and nothing strange after that
        if (strlen(token) > 1 && token[0] == ')'){
                token[1] = '\0';    
        }

        //printf("%s(%i)\n", token, strlen(token));

        //printf("(%i)\n", strlen(token));
        // sscanf is like scanf, but works on strings instead of stdin
        // if the token is an int       
        if (0.00 < sscanf(token, "%lf", &value)) {
            //printf("number: %s\n", token);
            // push the double on the stack
            push(s, create_node_number(value));
        } else {
            // the token is not an int, therefore it must be an operator (hopefully)
                    
            //Edit: Only pop and calculate the value if we reach a closing bracket -> )
            if (token[0] == ')'){                                
                
                //printf("Got a closing bracket\n");
                // pop the right operand
                struct element * rightEl = pop(s);
                //Make a decision: If it is a number, then just assign the value to right
                //If it is not, try looking for the variable with that name, and return its value to right
                if (rightEl->type == ELEMENT_NUMBER){
                    right =  rightEl->number;
                } else {
                    int var_index = find_var_index(rightEl->op);

                    //We can only evaluate the expression if the variable really exists
                    if (var_index != -1){
                        right = get_var_value(var_index);
                    } else {
                        //If it does not exist, terminate the evaluation an send a signal
                        //That the expression is invalid through the char * invalid Var
                        free(copy);
                        free_stack(s);
                            
                        *invalidVar = rightEl->op;
                        //Again, make sure nothing werid happen here
                        (*invalidVar)[strlen(rightEl->op)] = '\0';
                        return -1;
                    }
                }
                
                //pop the operator
                operator_found = pop(s)->op;
                

                //Determine if the operator_found is an '=' sign or not
                if (operator_found[0] == '='){

                    //pop the variable name
                    variable_found = pop(s)->op;

                    //Add that variable to the var_List
                    add_variable(var_List, variable_found, right);

                    value = right;

                } else { //Only evaluate as follow if it is not an '=' sign
                    
                    //pop the left operand
                    struct element * leftEl = pop(s);
                    //Make a decision: If it is a number, then just assign the value to left
                    //If it is not, try looking for the variable with that name, and return its value to left
                    if (leftEl->type == ELEMENT_NUMBER){
                        left =   leftEl->number;
                    } else {
                        int var_index = find_var_index(leftEl->op);

                        //We can only evaluate the expression if the variable really exists
                        if (var_index != -1){
                            left = get_var_value(var_index);
                        } else {
                            //If it does not exist, terminate the evaluation an send a signal
                            //That the expression is invalid through char * invalidVar
                            free(copy);
                            free_stack(s);

                            *invalidVar = leftEl->op;
                            //Again, make sure nothing weird happen here
                            (*invalidVar)[strlen(leftEl->op)] = '\0';
                            return -1;
                        }
                    }                    
                    //pop the open bracket -> throw it away
                    pop(s);

                    // evaluate the operator on left and right
                    //printf("operator: %s\n", token);
                    //value = operations[find_operation(operator_found)](left,right);
                    //printf("Get the operator: %s(%i) \n", operator_found, strlen(operator_found));
                    value = execute_operation(operator_found, left, right);                    
                    
                }

                //Whatever we do, the value is always pushed back the result onto the stack                
                push(s, create_node_number(value));

            } else {

                //Push back the value in if it is not a closing brace
                push(s, create_node_operator(token));


            }

                        
        }
        //printf("peek:%s\n", peek(s)->op);
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


