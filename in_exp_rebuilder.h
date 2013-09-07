#ifndef IN_REBUILDER
#define IN_REBUILDER

/**
 * Create a variable table for the mapping of
 * the variables may be used in the in-order processing
 */
bool is_Valid_Exp(char * input);

bool is_Full_Exp(char * input);

int find_string(char * input, char * toFind, int index_larger_than);

int advances_one_token(char * input, int current_index);

int go_back_one_token(char * input, int current_index);

void insert_char_before_index(char * input, int after_index, char char_to_insert);

void add_bracket_pairs(char * input, char * operator);

char * rebuild_in_exp(char * input);

#endif