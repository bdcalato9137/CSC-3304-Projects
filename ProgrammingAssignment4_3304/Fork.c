#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
 * This program uses a fork function to print numbers of a range from at least
 * one to any positive integer. The first half of the numbers are printed by the
 * parent process. The child process prints the other half.
 * 
 * CSC 3304 Programming Assignment No.4
 * 
 * @author Brennen Calato
 * @since 4/5/2021
 */
int main(int argc, char** argv) 
{
    if(argc < 3)
    {
        printf("Incorrect numbers of arguments\n");
        printf(": Success\n");
        printf("Usage: Fork <input filename> <output filename>\n");
        printf(": Success\n");
        return(EXIT_FAILURE);
    }
    //File pointer for the input file the program reads from
    FILE* fpr;
    //File pointer for the output file the program writes to
    FILE* fpw;
    //holds the process id to distinguish between the child and parent process
    pid_t pid;
    //creates a time variable for the current time
    time_t now;
    //number of outputs requested by the input file
    int numOfOutputs;
    //opens file with command line argument
    fpr = fopen(argv[1], "r");
    //takes in the number of outputs from the file and stores it
    fscanf(fpr, "%d\n", &numOfOutputs);
    //checks if the number of outputs is less than one and if so creates an error log.
    if(numOfOutputs < 1)
    {
        printf("An error has occurred. Please check the generated text file: \"ErrorLog\"\n");
        FILE* fpe;
        fpe = fopen("./ErrorLog.txt", "w");
        time(&now);
        fprintf(fpe, "Invalid Output Number Requested. Must be above -1. This Error occurred on %s", ctime(&now));
        fclose(fpe);
        return(EXIT_FAILURE);
    }
    //calculates how many numbers will output by the parent process
    int firstHalf = numOfOutputs/2;
    //opens a file for writing the process outputs
    fpw = fopen(argv[2], "w");
    //creates the parent and child process
    pid = fork();
    //both processes print that the fork is created to the console
    fprintf(fpw, "Fork Created...\n");
    //the parent process will print the half of the output numbers
    if(pid != 0)
    {
        for(int i = 1; i <= firstHalf; i++)
        {
            fprintf(fpw, "Parent process: %d\n", i);
        }
    }
    //the child process will output the second half of the output numbers
    else
    {
        for(int i = firstHalf + 1; i <= numOfOutputs; i++)
        {
            fprintf(fpw, "Child process: %d\n", i);
        }
    }
    
    //frees the file pointers
    fclose(fpr);
    fclose(fpw);
    
    return (EXIT_SUCCESS);
}

