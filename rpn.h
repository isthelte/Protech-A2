#ifndef RPN
#define RPN

void rpn_createVarList();

double rpn_eval(char *exp, char ** invalidVar, char ** otherExceptions);

int rpn_find_var_index(char * name);

double rpn_get_var_value(int index);

#endif
