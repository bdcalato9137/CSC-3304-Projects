#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SortingUtilities.h"

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
 * @since 3/14/2021
 */
void Swap(char** array1, char** array2)
{
    char* temp;
    
    temp = *array1;
    *array1 = *array2;
    *array2 = temp;
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
 * @since 3/14/2021
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


/**
 * This routine takes the string provided and strips it of its end of line marker
 * replacing it with a '/0'
 * 
 * routine: EOLDeleter
 * 
 * return type: void
 * 
 * parameters:
 *      line[MAX_LENGTH]      [char]        this is a string that will have its
 *                                          end of line marker stripped and
 *                                          replaced by '/0'
 * 
 * @author Brennen Calato
 * @since 3/14/2021
 */
void EOLDeleter(char line[MAX_LENGTH])
{
    //a pointer to a character used to identify the location of the '\n' character and replace it with '/0'
    char* pos;
    
    while((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';
}