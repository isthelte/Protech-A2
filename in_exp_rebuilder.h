#ifndef IN_REBUILDER
#define IN_REBUILDER

/**
 * Check if the expression is valid for rebuilding
 * by checking the number of open brackets and close brackets
 * @param char* the expression to be evaluated.
 * @return true if the 2 types of brackets are equal.
 */
bool is_Valid_Exp(char * input);

/**
 * Check if the expression is full expression, 
 * with all the () supported or not
 * @param char* the expression to be evaluated.
 * @return true if there are enough () so that the expression does not need to be rebuilt.
 */
bool is_Full_Exp(char * input);

/**
 * Find a sub-string in a larger string at is located only after a specified index 
 * . If nothing is found, the function returns -1
 * @param char* the expression to be evaluated.
 * @param char* the sub-string to be looked up
 * @param int the index of the big string from which the search start to look up 
 * @return the index of the sub-string in the large string
 */
int find_string(char * input, char * toFind, int index_larger_than);

/**
 * Assuming that all the token in the expression is separated by a ' '
 * .This function take the index of a token and return the index of the next token to the right.
 * .If the current index is at the end of the expression, it will return the current index
 * @param char* the expression to be evaluated.
 * @return the index of the next token
 */
int advances_one_token(char * input, int current_index);

/**
 * Assuming that all the token in the expression is separated by a ' '
 * .This function takes the index of a token and return the index of the previous token to the left.
 * .If the current index is at the beginning of the expression, it will return the current index
 * @param char* the expression to be evaluated.
 * @return the index of the previous token
 */
int go_back_one_token(char * input, int current_index);

/**
 * Assuming that all the token in the expression is separated by a ' '
 * .Insert a character and a ' ' before a character located at the index specified
 * @param char* the expression to be evaluated.
 * @param int the index after which the new character is inserted.
 * @param char the character to be inserted before the character at that index.
 */
void insert_char_before_index(char * input, int after_index, char char_to_insert);

/**
 * .This function finds the operator specified in the expression. If an expression is found,
 * it will find a left operand and right operand of that operator and "group" them using '(' and ')'
 * .If that operator has already been "group-ed", this function will do nothing
 * @param char* the expression to be evaluated.
 * @param char* the operator to be looked up.
 */
void add_bracket_pairs(char * input, char * operator);

/**
 * Takes in an incompleted in-order expression and return the full in-order expression,
 * with all the '(' and ')' needed to execute.
 * The result is allocated on the heap.
 * @param char* the incomplete expression to be evaluated.
 * @return a pointer to the complete version of the expression 
 */
char * rebuild_in_exp(char * input);

#endif