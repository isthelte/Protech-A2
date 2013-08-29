#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>    /* for getopt_long; standard getopt is in unistd.h */

#include "read_exp.h"
#include "rpn.h"
#include "in.h"
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

    do { 
        //Receive the input
        if (!isBatch){
            printf("s3372765>>>");
        }        
       
        length = read_exp(input);

        if (isEcho){
            printf("What you inputed is: %s\n", input);     
        }

        //Print out the ouput
        if (strcmp(input,"\0") != 0){
            printf("%lf\n", (isRPN) ? rpn_eval(input) : in_eval(input));
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
    printf("\nNo input received. This is considered as an exit.\n");
    printf("Program exits. Goodbye!!\n");

    exit (0);
}
