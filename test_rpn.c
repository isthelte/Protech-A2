#include <stdlib.h>
#include <stdio.h>
#include "rpn.h"

int main() {

	printf("\nTesting RPN expressions: \n");

    printf("4.25 5 + 12 - = %lf\n\n", rpn_eval("4.25 5 + 12 -"));
    printf("4 5 + 12 - 3 + = %lf\n\n", rpn_eval("4 5 + 12 - 3 +"));
    printf("4 5 1 2 + - 12 - - = %lf\n\n", rpn_eval("4 5 1 2 + - 12 - -"));
    
    printf("4 5 * 12 / = %lf\n\n", rpn_eval("4 5 * 12 /"));
    printf("4 5 + 12 / 3 + = %lf\n\n", rpn_eval("4 5 + 12 / 3 +"));
    printf("4 5 1 2 + * 12 - * = %lf\n\n", rpn_eval("4 5 1 2 + * 12 - *"));
    
    //Test the new operators
    //Power
    printf("2 5 ** = %lf\n\n", rpn_eval("2 5 **") );
    printf("2 -3 ** = %lf\n\n", rpn_eval("2 -3 **") );
    printf("-2 3 ** = %lf\n\n", rpn_eval("-2 3 **") );
    printf("-2 4 ** = %lf\n\n", rpn_eval("-2 4 **") );

    //Max
    printf("2 5 # = %lf\n\n", rpn_eval("2 5 #") );
    printf("-2 5 # = %lf\n\n", rpn_eval("-2 5 #") );
    printf("2 -5 # = %lf\n\n", rpn_eval("2 -5 #") );
    printf("-2 -5 # = %lf\n\n", rpn_eval("-2 -5 #") );

    //Min
    printf("2 5 _ = %lf\n\n", rpn_eval("2 5 _") );
    printf("-2 5 _ = %lf\n\n", rpn_eval("-2 5 _") );
    printf("2 -5 _ = %lf\n\n", rpn_eval("2 -5 _") );
    printf("-2 -5 _ = %lf\n\n", rpn_eval("-2 -5 _") );

    //Distance
    printf("2 5 || = %lf\n\n", rpn_eval("2 5 ||") );
    printf("-2 5 || = %lf\n\n", rpn_eval("-2 5 ||") );
    printf("2 -5 || = %lf\n\n", rpn_eval("2 -5 ||") );
    printf("-2 -5 || = %lf\n\n", rpn_eval("-2 -5 ||") );
}
