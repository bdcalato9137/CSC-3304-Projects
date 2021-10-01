#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SortingUtilities.h"
/**
 * This program will take an input of string values from a text file,
 * store those values in an array of strings, sort the array, and then print 
 * the sorted array into a separate text file
 * 
 * CSC 3304 Programming Project No.3
 * 
 * @author Brennen Calato
 * @since 3/14/2021
 */
int main()
{
    //the array of pointers to strings taken from the input file
    char** lineptr = calloc(10, sizeof(char*));
    
    //the character array that temporarily holds an input string until it is placed in the array
    char string[MAX_LENGTH];
    
    //the amount of strings in the input file
    int lines = 0;
    
    //the file pointer for the input file
    FILE* fpr;
    
    //the file pointer for the output file
    FILE* fpw;
    
    //this is a pointer to a character used to identify the location of the '\n' character and replace with with the '\0'
    char* pos;
    
    fpr = fopen("./TestInput.txt", "r");
    
    for(int i = 0; fgets(string, MAX_LENGTH, fpr) != 0; i++)
    {
        EOLDeleter(string);
        lineptr[i] = malloc((strlen(string)+1) * sizeof(char));
        strncpy(lineptr[i], string, strlen(string)+1);
        lines++;
        if(lines%10 == 0)
        {
            lineptr = realloc(lineptr, (lines+10)*sizeof(char*));
        }
    }
    fclose(fpr);
    
    lineptr = realloc(lineptr, lines * sizeof(char*));
    
    BubbleSort(lineptr, lines);
    
    fpw = fopen("./out.txt", "w");
    
    for(int i = 0; i < lines; i++)
    {
        if(i != (lines-1))
        {
            fprintf(fpw, "%s\n", lineptr[i]);
        }
        else
        {
            fprintf(fpw, "%s", lineptr[i]);
        }
    }
    fclose(fpw);
    
    for(int i = 0; i < lines; i++)
    {
        free(lineptr[i]);
    }
    free(lineptr);
    
    return 0;
}