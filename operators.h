#ifndef OPERATORS
#define OPERATORS

//Introduce the methods for the operations
double add(double a, double b);

double minus(double a, double b);

double multiply(double a, double b);

double divide(double a, double b);

double power(double a, double b);

double maximum(double a, double b);

double minimum(double a, double b);

double distance(double a, double b);

//Make 2 arrays: 1 for pointers and 1 for operation symbols
//extern double (* operations[])(double, double) = {add, minus, multiply, divide, maximum, minimum, distance, power};
//extern char * op_symbols[] = {"+", "-", "*", "/", "#", "_", "||", "**"};

//extern double (* operations[])(double, double);
//extern char * op_symbols[];

int find_operation(char * operator);

double execute_operation(char *operation , double a, double b);

#endif