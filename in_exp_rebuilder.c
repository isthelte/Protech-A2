#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool is_Valid_Exp(char * input){

	int open_bracket_counter = 0;
	int close_bracket_counter = 0;

	for (int i = 0; i < strlen(input); ++i)
	{
		//Count the number of open brackets
		if (input[i] == '('){
			open_bracket_counter++;
		}

		if (input[i] == ')'){
			close_bracket_counter++;
		}

	}

	//printf("(:%i ,op:%i\n", open_bracket_counter, operator_counter);

	//Return true if the number of '(' is equal to the number of operators
	if (open_bracket_counter == close_bracket_counter){
		return true;
	}

	return false;

}

bool is_Full_Exp(char * input){

	int open_bracket_counter = 0;
	int operator_counter = 0;

	for (int i = 0; i < strlen(input); ++i)
	{
		//Count the number of open brackets
		if (input[i] == '('){
			open_bracket_counter++;
		}

		//Count the number of operators
		//The Power **		
		if (input[i] == '*' && input[i+1] == '*'){
			operator_counter++;
			i++; //There's no need to check the char after i, since i and i+1 make 1 operator already
			continue;
		}

		//The Distance ||
		if (input[i] == '|' && input[i+1] == '|'){
			operator_counter++;
			i++; //There's no need to check the char after i, since i and i+1 make 1 operator already
			continue;
		}

		//...and other simple-1-character operators
		if (input[i] == '+'
			|| input[i] == '-'
			|| input[i] == '*'
			|| input[i] == '/'
			|| input[i] == '#'
			|| input[i] == '='
			|| input[i] == '_') {
			operator_counter++;
		}

	}

	//printf("(:%i ,op:%i\n", open_bracket_counter, operator_counter);

	//Return true if the number of '(' is equal to the number of operators
	if (open_bracket_counter == operator_counter){
		return true;
	}

	return false;

}

int find_string(char * input, char * toFind, int index_larger_than){	

	//Make one exception for the '=' operator: index_larger_than is treated as "index_smaller_than" -v-''
	if (strlen(toFind) == 1){ //This must be the equal sign "=", trust me!

		//printf("index larger = %i\n", index_larger_than );

		for (int i = strlen(input); i > 0; --i)
		{
			//printf("%c(%i) is compared to %c(%i)\n", input[i], i, toFind[0], 0 );

			if (input[i] == toFind[0] && i <= index_larger_than + 1){
				return i;
			}
		}

	} else { //This is the other ... operators

		for (int i = 0; i < strlen(input); ++i)
		{
			
			if (toFind[1] == ','){ //We know we're dealing with 2 operators

				//Add this to support 2 operators at the same time!
				char to_Find_1 = toFind[0];
				char to_Find_2 = toFind[2];

				if ((input[i] == to_Find_1 || input[i] == to_Find_2) && i >= index_larger_than + 1){
					return i;
				}
			} else {
				if (input[i] == toFind[0] && input[i+1] == toFind[1] && i >= index_larger_than + 2){
					return i;
				}
			}		
			
		}

	}	

	return -1;

}

//Assuming that the tokens are separated by ' '
int advances_one_token(char * input, int current_index){
	
	int jump_to_index = current_index;

	//Keep moving forward until we find a ' ', then jump forward 1 more char,
	//And we should arrive at the next token
	while (input[jump_to_index] != ' '){

		//If we come across the end of the string, just quit
		//We won't find any ' ' from here onward
		if (input[jump_to_index] == '\0'){
			return ++jump_to_index;
		}

		jump_to_index++;	
	}

	return ++jump_to_index;
}

int go_back_one_token(char * input, int current_index){

	int jump_to_index = current_index;
	int space_char_counter = 0;

	//Keep moving forward until we find a second ' ', then jump forward 1 more char,
	//And we should arrive at the previous token
	//There is one exception though:
	//If we reach the beginning of the string, we won't go any further
	while (jump_to_index != 0){

		if (input[jump_to_index] == ' '){
			//printf("Got one space char at index %i\n", jump_to_index);
			space_char_counter++;			
		}

		//If we got enough space char we want, quit
		if (space_char_counter == 2){
			break;
		}

		jump_to_index--;	

		//If we come across the beginning of the string, quit
		if (jump_to_index == 0){
			return jump_to_index;
		}
	}

	return ++jump_to_index;

}

void insert_char_before_index(char * input, int after_index, char char_to_insert){

	int old_length = strlen(input);

	//printf("%c\n", input[strlen(input) + 2]);

	//printf("Reach here\n");

	//Move all the char starting from the after_index 2 slots to the right
	for (int i = old_length; i >= after_index; --i)
	{
	 	input[i + 2] = input[i];
	}	

	//Put '\0' at the new end
	input[old_length + 2] = '\0';

	//Insert the new character at the position that has just been moved
	input[after_index] = char_to_insert;
	//To make sure, the position right after this is a space
	input[after_index + 1] = ' ';

}

void add_bracket_pairs(char * input, char * operator){
	
	int checkpoint = (operator[0] != '=') ? 0 : strlen(input) - 1;

	do
	{
		checkpoint = find_string(input, operator, checkpoint);

		//printf("get checkpoint: %i \n", checkpoint );

		if (checkpoint != -1) {

			//printf("Found an operator %s at index %i\n", operator, checkpoint);		

			/*
			 *Try adding a ')'
			 */
			//printf("Try adding a ')'\n");

			//printf("Old string is: %s\n", input);

			//printf("Old length is: %i\n", strlen(input));

			int index_forward = advances_one_token(input, checkpoint);

			//printf("We're now at [%i]->%c\n", index_forward, input[index_forward]);
			//printf("The next token would be [%i]->%c\n", advances_one_token(input, index_forward) ,input[advances_one_token(input, index_forward)]);			

			int count_group_exp_forward = 0; //This will count the number of group exp we come across as we go through
			int go_forward_index = checkpoint; //This will remember the index we're going through

			if (input[index_forward] == '('){ //Uh-oh, we didn't find a number, but another group of exp!
				count_group_exp_forward++;
				go_forward_index = advances_one_token(input, go_forward_index);
			} else if (input[advances_one_token(input, index_forward)] == ')' && advances_one_token(input, index_forward) <= strlen(input) - 1){ //If it has already been done
				continue; //skip the task
			} else { //If we didn't, then we're fine
				go_forward_index = advances_one_token(input, go_forward_index);				
			}

			//We will keep going forward until there is no more group of exp
			while (count_group_exp_forward != 0){

			    go_forward_index = advances_one_token(input, go_forward_index);

				if (input[go_forward_index] == ')'){
					count_group_exp_forward--;
				}

				if (input[go_forward_index] == '('){
					count_group_exp_forward++;
				}

			}

			//Now determine if we're at the end of the string or not
			go_forward_index = advances_one_token(input, go_forward_index);
			if (go_forward_index >= strlen(input) - 1){
				//If we're really at the end of the string *sigh*
				//Do as follows:			
				//printf("We got here\n");
				//printf("..and got the char %c\n", input[go_forward_index - 2]);	
				input[go_forward_index - 1] = ' '; //Remove the '\0' out
				input[go_forward_index] = ')'; //Add the ')' bracket
				input[go_forward_index + 1] = '\0'; //End the string
			} else {
				//If we're not at the end, then it's easy:
				//Just insert the ')' before the token we're currently accessing
				insert_char_before_index(input, go_forward_index, ')');				
			}
			
			//printf("the input is now %s\n", input);

			//printf("New length is: %i\n\n", strlen(input));	

			/*
			 *Try adding a '('
			 */
			//printf("Try adding a '('\n");

			//printf("Old string is: %s\n", input);

			//printf("Old length is: %i\n", strlen(input));

			int index_backward = go_back_one_token(input, checkpoint);

			//printf("Checkpoint = %i\n",  checkpoint);
			//printf("Index backward = %i\n", index_backward );			

			int count_group_exp_backward = 0; //This will count the number of group exp we come across as we go through
			int go_back_index = checkpoint; //This will remember the index we're going through

			if (input[index_backward] == ')'){ //Uh-oh, we didn't find a number, but another group of exp!
				count_group_exp_backward++;
				go_back_index = go_back_one_token(input, go_back_index);
			} else { //If we didn't, then we're fine
				go_back_index = go_back_one_token(input, go_back_index);
			}

			//We will keep going back until there is no more group of exp
			while (count_group_exp_backward > 0 ){

			    go_back_index = go_back_one_token(input, go_back_index);
			    //printf("Got to %c at index %i\n", input[go_back_index], go_back_index );

				if (input[go_back_index] == '('){
					count_group_exp_backward--;
				}

				if (input[go_back_index] == ')'){
					count_group_exp_backward++;
				}

				//printf("count group: %i\n", count_group_exp_backward);

			}

			insert_char_before_index(input, go_back_index, '(');			

			//printf("the input is now %s\n", input);

			//printf("New length is: %i\n\n", strlen(input));				

			//Of course, adding a '(' and a space will 'push' the checkpoint to the right by 2 slots
			//This, however, is not relevant to the '=' operator, since it is processed from right to left
			checkpoint += (operator[0] != '=') ? 2 : 0; 

		}

	} while (checkpoint != -1);	

}

//Ok, this is it, time to shine ....
char * rebuild_in_exp(char * input){

	//Make a copy, just ... to be sure
	char * result = malloc(101);
	strcpy (result, input); 

	//Add the brackets to the operations in precendence order:

	//Phase 1: **
	add_bracket_pairs(result, "**");
	//Phase 2: * and /
	add_bracket_pairs(result, "*,/");
	//Phase 3: + and -
	add_bracket_pairs(result, "+,-");
	//Phase 4: # and _
	add_bracket_pairs(result, "#,_");
	//Phase 5: ||
	add_bracket_pairs(result, "||");
	//Phase 6: =
	add_bracket_pairs(result, "=");

	return result;

}

//Uncomment the below if you want to re-test this feature one day ....
/*
int main(){
	
	char input[100];
	strcpy (input, "( 2.4 + 6.2 ) * 2.1 / 3.9"); 
	char input_full[] = "( ( 6 + 3 ) ** 2 )";

	printf("input is %s: %s\n", input, (is_Full_Exp(input)) ? "a full exp" : "not a full exp");	
	printf("input_full is %s: %s\n", input_full, (is_Full_Exp(input_full)) ? "a full exp" : "not a full exp");

	printf("\nLet's start advancing token for input!\n");

	printf("Start from index 0\n");

	int jump_to_index = 0;
	do
	{
		printf("[%i]->", jump_to_index);

		printf("%c\n", input[jump_to_index]);

	 	jump_to_index =  advances_one_token(input, jump_to_index);

	} while (jump_to_index <= strlen(input) - 1);

	printf("\n\nLet's start advancing token for input, reverse way!\n");

	printf("Start from index at the end of the string\n");

	int jump_to_index_2 = strlen(input) - 3;
	do
	{
		printf("[%i]->", jump_to_index_2);

		printf("%c\n", input[jump_to_index_2]);

		if (jump_to_index_2 == 0){
	 		break;
	 	}

	 	jump_to_index_2 =  go_back_one_token(input, jump_to_index_2);

	} while (jump_to_index_2 >= 0);


	printf("\n\nStart adding brackets to the input\n");
	
	//Phase 1: **
	add_bracket_pairs(input, "**");
	//Phase 2: * and /
	add_bracket_pairs(input, "*,/");
	//Phase 3: + and -
	add_bracket_pairs(input, "+,-");
	//Phase 4: # and _
	add_bracket_pairs(input, "#,_");
	//Phase 5: ||
	add_bracket_pairs(input, "||");

	printf("Input now is: %s\n", input);

	//free(input);

	char * input = "1 * 2 * 3 * 4 * 5";

	printf("In: %s\n", input);

	char * result = rebuild_in_exp(input);

	printf("Out: %s\n", result);
}*/

