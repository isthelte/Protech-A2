#ifndef EXP_TREE
#define EXP_TREE

enum et_node_type {ET_NUMBER, ET_OPERATOR};

/**
 * Expression tree node struct.
 */
struct et_node {
    enum et_node_type type;              
    union {
        double number;      /**< the number to store in the node */
        char op[2];         /**< an operator has at most 2 chars */
    };
    struct et_node *left;   /**< pointer to the left child node of this node */
    struct et_node *right;  /**< pointer to the right child node of this node */
};

/**
 * There are 3 ways to go through an expression tree nodes : preorder, inorder and
 * postorder. 
 */
enum et_order {PREORDER, INORDER, POSTORDER};

/**
 * Create an expression tree number node.
 * The new node will be allocated on the heap.
 * @param number the number to put inside the node.
 * @return pointer to the new node.
 */
struct et_node * et_create_number_node(double number);
                                        
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
                                          struct et_node *right);

/**
 * Create an expression tree from a string expression.
 * The new nodes will be allocated on the heap.
 * @param exp the expression to parse and to build the tree from.
 * @param order extression tree order in which to process the expression.
 * @return pointer to the root node of the new expression tree.
 */
struct et_node * et_create(char *exp, enum et_order order);

/**
 * Free the memory used by an expression tree.
 * @param node pointer to the node to free.
 */
void et_free(struct et_node *node);   

/**
 * Evaluate an expression tree.
 * @param node pointer to the node to evaluate.
 * @return the value of the expression.
 */
double et_eval(struct et_node *node);                     
                                      
/**
 * Print an expression tree node (non-recursive).
 * @param node pointer to the node to print.
 */
void et_print_node(struct et_node *node);

/**
 * Print an expression tree (recursive).
 * @param node pointer to the node to print.
 * @param order order in which to print the binary tree nodes.
 */
void et_print(struct et_node *node, enum et_order order);    
                                    
#endif