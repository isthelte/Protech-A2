#ifndef VARIABLES_MAPPING
#define VARIABLES_MAPPING
#include <stdbool.h>

#define SIZE 5

/**
 * Varialbe table struct.
 */
struct table {
	char ** names;			/**< the array for storing variable name (string) */
	double * values;		/**< the array for storing variable value */
	int curOccupancy;		/**< the current occupancy of the 2 arrays */
};

/**
 * Initialize a variable table for the mapping of
 * the variables may be used in the in-order / RPN processing.
 * By default, the size of this table is 5
 * @return the pointer to the table.
 */
struct table * createTable();

/**
 * Look up a variable name in the variable table
 * This function returns the index of the variable in the table (if found).
 * If nothing is found, this function returns -1.
 * @param t the pointer to the table.
 * @param name the variable name to look up.
 * @return the index of the variable in the table.
 */
int find_variable(struct table * t, char * name);

/**
 * Resize the table to a new size
 * The new size is equal to the old size + 5
 * @param t the pointer to the table.
 */
void table_resize(struct table * t);

/**
 * Add a variable to the table
 * @param t the pointer to the table.
 * @param name the variable name.
 * @param value the variable's value.
 * @return the index of the variable in the table.
 */
void add_variable(struct table * t, char * name, double value);

/**
 * Retrieve the value of a variable at the specified index
 * @param t the pointer to the table.
 * @param var_index the index of the variable in the table.
 * @return the value of the variable in the table.
 */
double get_variable(struct table * t, int var_index);

/**
 * Modify the value of a variable in the table
 * @param t the pointer to the table.
 * @param var_index the index of the variable in the table.
 * @param newValue the new value of the variable.
 */
void edit_variable(struct table * t, int var_index, double newValue);

#endif