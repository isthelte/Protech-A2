#ifndef IN
#define IN

void createVarList();

double in_eval(char *exp, char ** invalidVar);

int find_var_index(char * name);

double get_var_value(int index);

#endif