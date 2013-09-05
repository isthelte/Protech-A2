#include <stdlib.h>
#include <stdio.h>

#include "exp_tree.h"

/**
 * Create an expression tree number node.
 * The new node will be allocated on the heap.
 * @param number the number to put inside the node.
 * @return pointer to the new node.
 */
struct et_node * et_create_number_node(double number){
	struct et_node *node = malloc(sizeof(struct et_node));

	node->type = ET_NUMBER;
	node->number = number;

	return node;
}
                                        
/**
 * Create an expression tree operator node.
 * The new node will be allocated on the heap.
 * @param op the operator to put inside the node.
 * @param left pointer to the left child node of this node.
 * @param right pointer to the right child node of this node.
 * @return pointer to the new node.
 */
struct et_node * et_create_operator_node(char op[], 
                                          struct et_node *left, 
                                          struct et_node *right){
	struct et_node *node = malloc(sizeof(struct et_node));

	node->type = ET_OPERATOR;
	node->op = op;
	node->left = left;
	node->right = right;

	return node;
}

/**
 * Create an expression tree from a string expression.
 * The new nodes will be allocated on the heap.
 * @param exp the expression to parse and to build the tree from.
 * @param order extression tree order in which to process the expression.
 * @return pointer to the root node of the new expression tree.
 */
struct et_node * et_create(char *exp, enum et_order order){
    
}

/**
 * Free the memory used by an expression tree.
 * @param node pointer to the node to free.
 */
void et_free(struct et_node *node);  {
	if (node != NULL) {
        et_free(node->left);
        et_free(node->right);
        free(node);
    }
}

/**
 * Evaluate an expression tree.
 * @param node pointer to the node to evaluate.
 * @return the value of the expression.
 */
double et_eval(struct et_node *node){
    
}
                                      
/**
 * Print an expression tree node (non-recursive).
 * @param node pointer to the node to print.
 */
void et_print_node(struct et_node *node){
	(node->type == ET_OPERATOR) 
		? printf("%s\n", node->op) 
		: printf("%lf\n", node->number);
}

/**
 * Print an expression tree (recursive).
 * @param node pointer to the node to print.
 * @param order order in which to print the binary tree nodes.
 */
void et_print(struct et_node *node, enum et_order order){
	if (node == NULL) {
        printf("[]\n");
    } else {
        if (order == PREORDER) {
            et_print_node(node);
            et_print(node->left, order);
            et_print(node->right, order);
        } else {
            if (order == INORDER) {
                et_print(node->left, order);
                et_print_node(node);
                et_print(node->right, order);
            } else {
                et_print(node->left, order);
                et_print(node->right, order);
                et_print_node(node);
            }
        }
    }
}  