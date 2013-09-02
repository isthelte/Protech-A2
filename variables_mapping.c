#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "variables_mapping.h"

struct table *  createTable(){
	struct table * t = malloc(sizeof(struct table));
	//Create 2 arrays: 1 for storing variable name (string), one for storing variable value
	//Create an array of strings of length 50
	char ** var_names;
	var_names = malloc(sizeof(char*)*SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		var_names[i] = malloc(50 * sizeof(char)); //We assume that a variable cannot have a length > 50
	}
	t->names = var_names;
	t->values = malloc(sizeof(double)*SIZE);
    //Create an int to give us an idea of the current occupancy of the 2 arrays
	//At the beginning, this value is 0 (we have nothing there yet)
	t->curOccupancy = 0;

	return t;
}

int find_variable(struct table * t, char * name){
	//Loop and find (linear-search)
	for (int i = 0; i < t->curOccupancy; ++i)
	{
		if (strcmp(name, t->names[i]) == 0){
			return i;
		}
	}

	return -1;
}

void table_resize(struct table * t){
	//Create 2 new array
	//Create an array of strings of length 50
	char ** var_names;
	var_names = malloc(sizeof(char*)*SIZE + t->curOccupancy);
	for (int i = 0; i < SIZE; ++i)
	{
		var_names[i] = malloc(50 * sizeof(char)); //We assume that a variable cannot have a length > 50
	}
	char ** names_new = var_names;
	double * values_new = malloc(sizeof(double)*(SIZE + t->curOccupancy));

	//Copy the values from the old arrays to the new arrays
	for (int i = 0; i < t->curOccupancy; ++i)
	{
		names_new[i] = t->names[i];
		values_new[i] = t->values[i];
	}

	//Retain the pointer to the 2 old arrays
	char ** names_old = t->names;
	double * values_old = t->values;

	//Assign the 2 new array to name and value
	t->names = names_new;
	t->values = values_new;

	//Free up the 2 old array
	free(names_old);
	free(values_old);
}

void add_variable(struct table * t, char * name, double value){

	//We check if the arrays have reached their limit size
	//For example, if the SIZE is set to 3, and the curOccupancy is 3,
	//then we need to resize the table to size of 3 + SIZE = 6
	//if the size is 6, for example, we follow the same philosophy
	//and set the new size to 6 + SIZE = 9
	if (t->curOccupancy % SIZE == 0 && t->curOccupancy != 0){
		table_resize(t);
	}

	//The current occupancy also shows the next empty index in the 2 arrays
	//For example, if the array currently has 2 values (currOccupancy = 2) in index 0 and 1, this means
	//that the next empty index is 2
	t->names[t->curOccupancy] = name;
	t->values[t->curOccupancy] = value;

	//Since we added a new variable, update the currOccupancy
	t->curOccupancy++;
}

double get_variable(struct table * t, int var_index){
	//printf("in table: %s(%i) = %lf\n", t->names[0], strlen(t->names[0]), t->values[0]);
	return t->values[var_index];
}

bool edit_variable(struct table * t, char * name, double newValue){

	int var_index = find_variable(t, name);
	//printf("Found variable %s at index %i\n", name, var_index);

	if(var_index != -1){
		t->values[var_index] = newValue;
		return true;
	}

	return false;
	
}