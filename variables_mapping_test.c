#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "variables_mapping.h"

int main(){

	struct table * t = createTable(); 

	printf("- Add variable myVar = 1.5\n");
	add_variable(t, "myVar", 1.5);

	printf("- Add variable notMyVar = 2.5\n");
	add_variable(t, "notMyVar", 2.5);

	printf("- Add variable hereHaveAnotherVar = 3.5\n");
	add_variable(t, "hereHaveAnotherVar", 3.5);

	printf("- Add variable theFinalVar = 4.5\n");
	add_variable(t, "theFinalVar", 4.5);

	printf("\n");
	printf("- Edit variable notMyVar = 2.5 to 9.5 ... %s", edit_variable(t, "notMyVar", 9.5) ? "Success!" : "Fail");	

	printf("\n\n");
	printf("Looking for theFinalVar, get: %lf\n", get_variable(t, "theFinalVar") );

	printf("Looking for notMyVar, get: %lf\n", get_variable(t, "notMyVar") );

	return 1;
}