#include "read_exp.h"
#include <stdio.h> 



// read a string into exp (must be allocated by the caller, 
// at least MAX_EXP_LENGTH+1 characters in length)
int read_exp(char *exp) {
    int ccount = 0;
    char c;
    
    c = getchar();
    // read until reaching a new line character or the maximum length
    while (c != '\n' && ccount < MAX_EXP_LENGTH) {
        if (c == EOF) {
            // return -1 if the end-of-file EOF has been reached
            return -1;
        }
        exp[ccount] = c;
        ccount++;
        c = getchar();
    }
    // put an end of string character at the end
    exp[ccount] = '\0';
    
    // return the character count (number of characters read)
    return ccount;
}
