#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LENGTH 101
#define MAX_LINES 500

//declaration for BubbleSort
void BubbleSort(char* ptrArray[], int size);
//declaration for Swap
void Swap(char** array1, char** array2);

/**
 * This program will take an input of string values from a text file,
 * store those values in an array of strings, sort the array, and then print
 * the sorted array into a separate text file.
 * 
 * CSC 3304 Programming Project No.1
 * 
 * @author Brennen Calato
 * @since 2/11/2021
 */
int main()
{
    //the array of pointers to strings taken from the input file
    char* lineptr[MAX_LINES];
    
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
    
    for(int i = 0; fgets(string, MAX_LENGTH, fpr) != 0 && lines < MAX_LINES; i++, lines++)
    {
        while((pos=strchr(string, '\n')) != NULL)
            *pos = '\0';
        lineptr[i] = malloc((strlen(string)+1) * sizeof(char));
        strncpy(lineptr[i], string, strlen(string));
    }
    fclose(fpr);
    
    BubbleSort(lineptr, lines);
    
    fpw = fopen("./out.txt", "w");
    
    for(int i = 0; i < lines; i++)
    {
        fputs(lineptr[i], fpw);
        if(i < lines - 1)
            fputs("\n", fpw);
    }
    fclose(fpw);
    
    for(int i = 0; i < lines; i++)
    {
        free(lineptr[i]);
    }
    
    return 0;
}

/*
 * This routine takes the provided pointer array and sorts
 * the strings pointed to by the array.
 * 
 * routine: BubbleSort
 * 
 * return type: void
 * 
 * parameters:
 *      ptrArray[]       [char*]    the array of string pointers
 *      size             [int]      the size of the array(the amount of strings)
 * 
 * @author Brennen Calato
 * @since 2/11/2021
 */
void BubbleSort(char* ptrArray[], int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(strcmp(ptrArray[i], ptrArray[j]) > 0)
            {
                Swap(&ptrArray[i], &ptrArray[j]);
            }
        }
    }
}

/*
 * This routine is used by the BubbleSort and swaps the location of two strings
 * in an array if they are out of order
 * 
 * routine: Swap
 * 
 * return type: void
 * 
 * parameters:
 *      array1      [char**]     A pointer to a pointer of a string going to be 
 *                               swapped with the string following it
 *      array2      [char**]     A pointer to a pointer of a string going to be 
 *                               swapped with the string preceding it
 * 
 * @author Brennen Calato
 * @since 2/11/2021
 */
void Swap(char** array1, char** array2)
{
    char* temp;
    
    temp = *array1;
    *array1 = *array2;
    *array2 = temp;
}
