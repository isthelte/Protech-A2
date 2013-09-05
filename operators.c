#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

/*double power(double a, double b){    
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
}*/

double power(double a, double b){
    return pow(a, b);    
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

double execute_operation(char *operation , double a, double b){

    return operations[find_operation(operation)](a, b);

}
