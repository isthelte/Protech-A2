#ifndef OPERATORS
#define OPERATORS

/**
 * Add two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double add(double a, double b);

/**
 * Substract two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double minus(double a, double b);

/**
 * Multiply two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double multiply(double a, double b);

/**
 * Divide two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double divide(double a, double b);

/**
 * Calculate the power of the first number to the second number.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double power(double a, double b);

/**
 * Find the maximum between two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double maximum(double a, double b);

/**
 * Find the minimum between two numbers.
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double minimum(double a, double b);

/**
 * Find the absolute distance between two numbers (or | a - b |).
 * @param a the first operand.
 * @param b the second operand
 * @return the result.
 */
double distance(double a, double b);

//Make 2 arrays: 1 for pointers and 1 for operation symbols
//extern double (* operations[])(double, double) = {add, minus, multiply, divide, maximum, minimum, distance, power};
//extern char * op_symbols[] = {"+", "-", "*", "/", "#", "_", "||", "**"};

//extern double (* operations[])(double, double);
//extern char * op_symbols[];

/**
 * Find the operator in the list of possible operations.
 * If nothing is found, this function returns -1.
 * @param operator the operator to find.
 * @return the index of the operator in the array.
 */
int find_operation(char * operator);

/**
 * Execute the operation on the 2 operands based on the given operator
 * @param operation the operator to determine the operation.
 * @param a the first operand
 * @param b the second operand
 * @return the result.
 */
double execute_operation(char *operation , double a, double b);

#endif