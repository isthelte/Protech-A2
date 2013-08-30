#ifndef VARIABLES_MAPPING
#define VARIABLES_MAPPING

#define SIZE 3

struct table {
	//Create 2 arrays: 1 for storing variable name (string), one for storing variable value
	char ** names;
	double * values;
    //Create an int to give us an idea of the current occupancy of the 2 arrays
	int curOccupancy;
};

struct table * createTable();

int find_variable(struct table * t, char * name);

void resize(struct table * t);

void add_variable(struct table * t, char * name, double value);

double get_variable(struct table * t, char * name);

bool edit_variable(struct table * t, char * name, double newValue);

#endif