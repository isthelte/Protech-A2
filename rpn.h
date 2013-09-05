#ifndef RPN
#define RPN

/**
 * Create a variable table for the mapping of
 * the variables may be used in the in-order processing
 */
void rpn_createVarList();

/**
 * Find the variable in the variables table.
 * This function will return the index of the variable if it is found.
 * If nothing is found, the function returns -1.
 * @param name the variable name to find.
 * @return the index of the variable.
 */
int rpn_find_var_index(char * name);

/**
 * Use the index and retrieve the value of the variable in the variables table.
 * @param index index of the variable name to retrieve value.
 * @return the value of the variable.
 */
double rpn_get_var_value(int index);

/**
 * Evaluate the expression and return the result.
 * Any error occured will modify the 2 strings invalidVar and otherExceptions from "" to a text.
 * @param exp the expression to be evaluated.
 * @param invalidVar String to notify if an invalid / undeclared variable is found.
 * @param ptherExceptions String to notify other error, such as invalid expression.
 * @return the value of the expression.
 */
double rpn_eval(char *exp, char ** invalidVar, char ** otherExceptions);

#endif
