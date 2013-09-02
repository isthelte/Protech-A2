#ifndef IN
#define IN

void in_createVarList();

double in_eval(char *exp, char ** invalidVar, char ** invalidAssignment);

int in_find_var_index(char * name);

double in_get_var_value(int index);

#endif