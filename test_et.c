#include <stdlib.h>
#include <stdio.h>
#include "exp_tree.h"
#include "et_stack.h"

int main() {
    char post[] = "4 5 + 12 / 3 +";//"4.00 5.00 1.00 2.00 + - 12.00 - -"
    char in[] = "( ( ( 4.00 + 5.00 ) / 12.00 ) + 3.00 )";//( 4.00 - ( ( 5.00 - ( 1.00 + 2.00 ) ) - 12.00 ) )";
    struct et_node *root;
    root = et_create(post, POSTORDER);
    et_print(root, POSTORDER);
    printf("\n");
    et_print(root, INORDER);
    printf("\n");
    printf("Value: %.2lf\n", et_eval(root));
    
    et_free(root);
    
    root = et_create(in, INORDER);
    et_print(root, POSTORDER);
    printf("\n");
    et_print(root, INORDER);
    printf("\n");
    printf("Value: %.2lf\n", et_eval(root));    
}
