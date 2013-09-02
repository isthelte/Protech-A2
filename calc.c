#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>    /* for getopt_long; standard getopt is in unistd.h */

#include "read_exp.h"
#include "rpn.h"
#include "in.h"
#include "variables_mapping.h"
#include <stdbool.h>
#include <string.h>

int main (int argc, char **argv) {
    int c;
    //int digit_optind = 0;
    //int aopt = 0, bopt = 0;
    //char *copt = 0, *dopt = 0;
    static struct option long_options[] = {
        /*
            Customized version
        */
        {"rpn", 0, 0, 0},
        {"in", 0, 0, 0},
        {NULL, 0, NULL, 0}
    };
    int option_index = 0;

    //Store the 2 args
    bool isEcho = false;
    bool isBatch = false;
    bool isRPN = false; //This will determine if the program use rpn or in 

    while ((c = getopt_long(argc, argv, "be",
                 long_options, &option_index)) != -1) {
        //int this_option_optind = optind ? optind : 1;        

        switch (c) {

        case 0:
            if (strcmp(long_options[option_index].name, "rpn") == 0){
                isRPN = true;
            }
            break;        
        case 'b':
            isBatch = true;
            break;                                                      
        case 'e':
            isEcho = true;
            break;  
        default:        
            printf("-------Program NOTICE-----------\n");            
            printf("The argument is invalid.\n");
            printf("To prevent unwanted bugs. The program will now exit.\n");
            printf("Please try again with the correct following format:\n");
            printf("\t./calc [options] rpn|in\n");
            printf("\t- [options] can be -b and/or -e or simply nothing.\n");
            printf("\t- rpn|in should be either --rpn or --in\n");
            exit (0);
            break;     
        }
    }

    if (optind < argc) {
        printf ("non-option ARGV-elements: ");
        while (optind < argc)
            printf ("%s ", argv[optind++]);
        printf ("\n");
    }

    //Here is the program:
    printf("The program is run with the following mode:\n");
    printf("\t- Batch mode: %s\n", (isBatch) ? "ON" : "OFF" );
    printf("\t- Echo mode: %s\n", (isEcho) ? "ON" : "OFF" );
    printf("\t- Using option: %s\n", (isRPN) ? "RPN" : "IN" );
    printf("--------------------------------------\n\n");

    int length;
    char *input = malloc(sizeof(char)*MAX_EXP_LENGTH+1);    
    createVarList();

    do { 

        //Receive the input
        if (!isBatch){
            printf("s3372765>>>");
        }        
       
        length = read_exp(input);

        //Try to 'cut-off' the weird character with ASCII code 13 out of the input
        //P/s: 13 is the ASCII code of 'carriage return', how the hell can it end up here? Isn't it \n?
        if (input[strlen(input) - 1] == 13){
            input[strlen(input) - 1] = '\0';
        }

        if (isEcho){
            printf("What you input is: %s\n", input);
        }

        //Print out the ouput
        if (strcmp(input,"\0") != 0){
            if (isRPN){
                printf("%s = %lf\n", input, rpn_eval(input));
            } else {                
                //If we cant find any " " , then there must be a variable there, try to print it out!
                if (strstr(input, " ") == NULL){
                    //printf("input is %s(%i)\n", input, strlen(input));

                    //Find if the variable actually exist first
                    int var_ind = find_var_index(input);

                    //Only return the variable value if we can find the variable
                    if (var_ind != -1){
                        printf("%s = %lf\n", input, get_var_value(var_ind));                        
                    } else { 
                        //If the variable does not exist, print out a meaningful error mes
                        printf("Unrecognized variable name '%s'\n", input );
                    }
                    
                } else {
                    //Create a char* to show the invalid Variable
                    char * invalidVariable = malloc(sizeof(char)*50);
                    invalidVariable[0] = '\0';

                    double result = in_eval(input, &invalidVariable);

                    //printf("%s\n", (invalidVariable[0] == '\0') ? "There is no error" : "There is an error" );
                    //If there is no error, print out the result
                    if (invalidVariable[0] == '\0'){
                        printf("%s = %lf\n", input, result);
                    } else {
                        //If there is an error, print out the error
                        printf("Unrecognized variable name '%s'. The evaluation is terminated \n", invalidVariable);
                    }

                    //Free the string when we're done
                    //free(invalidVariable); //Commented out because it's causing trouble: *** glibc detected *** ./calc: free(): invalid pointer: 0x0966f364 ***
                    
                }                
            }
        }

        //"Clean" the string by hand (P/s: IS THERE NO OTHER WAY? #$%#$@#$@#$#@)
        for (int i = 0; i < MAX_EXP_LENGTH + 1; ++i)
        {
            input[i] = '\0';
        }        

    } while (length > 0);

    free(input);
    
    //Print out the exit
    printf("\n--------------------------------------");
    printf("\nNo other input received. This is considered as an exit.\n");
    printf("Program exits. Goodbye!!\n");

    exit (0);
}
