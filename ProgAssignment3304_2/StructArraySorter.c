#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINES  500
#define MAX_LENGTH  100

//Structure for a media type of book or music
struct musicOrBook
{
    //a pointer to the creator of the book/music
    char* creator;
    //a pointer to the genre of the book/music
    char* genre;
    //a pointer to the year the book/music was published/released
    char* year;
};
//Structure for a media type of movie
struct movie
{
    //a pointer to the rating of the movie
    char* rating;
    //a pointer to the year the movie was released
    char* year;
};

//Overall structure for all media types
struct media
{
    //a pointer to the type of the media
    char* type;
    //a pointer to the name of the media
    char* name;
    //a union containing the two different structures used for the media types
    union mediaType
    {
        //structure for a book or music
        struct musicOrBook musicBook;
        //structure for a movie
        struct movie Movie;
    }pmt;
    //the above pmt is a pointer to the union media 
};

//declaration for BubbleSort
void BubbleSort(struct media* ptrArray[], int size);
//declaration for Swap
void Swap(struct media** media1, struct media** media2);
//declaration for EOLDeleter
void EOLDeleter(char line[MAX_LENGTH]);

/**
 * This program take different media types from an input file, and stores their
 * attributes such as type, name genre, etc. into corresponding structures. It
 * then stores those structures into an array of structure pointers which is 
 * used to sort the different medias by their name(ascending).
 * 
 * CSC 3304 Programming Project No 2
 * 
 * @author Brennen Calato
 * @since 2/25/2021
 */
int main() 
{
    //an array of pointers that point to the different structures made from the input file
    struct media* arrayOfStructs[MAX_LINES];
    
    //a string used to store the input lines from the input file while they are being added to the structures.
    char string[MAX_LENGTH];
    
    //the total amount of structures created
    int arrayCount = 0;
    
    //the file pointer for the input file
    FILE* fpr;
   
    //the file pointer for the output file
    FILE* fpw;
    
    fpr = fopen("./TestInput.txt", "r");
    
    for(int lines = 0; fgets(string, MAX_LENGTH, fpr) != 0 && lines < MAX_LINES; arrayCount++)
    {
        arrayOfStructs[arrayCount] = (struct media*)malloc(sizeof(struct media));
        EOLDeleter(string);
        if(strcmp(string, "music") == 0 || strcmp(string, "book") == 0)
        {
            arrayOfStructs[arrayCount]->type = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->type, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->name = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->name, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->pmt.musicBook.creator = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->pmt.musicBook.creator, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->pmt.musicBook.genre = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->pmt.musicBook.genre, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->pmt.musicBook.year = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->pmt.musicBook.year, string, strlen(string)+1);
            
            lines+= 5;
        }
        
        else if(strcmp(string, "movie") == 0)
        {
            arrayOfStructs[arrayCount]->type = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->type, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->name = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->name, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->pmt.Movie.rating = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->pmt.Movie.rating, string, strlen(string)+1);
            fgets(string, MAX_LENGTH, fpr);
            EOLDeleter(string);
            arrayOfStructs[arrayCount]->pmt.Movie.year = malloc((strlen(string)+1) * sizeof(char));
            strncpy(arrayOfStructs[arrayCount]->pmt.Movie.year, string, strlen(string)+1);
            
            lines += 4;
        }
    }
    
    fclose(fpr);
    
    BubbleSort(arrayOfStructs, arrayCount);
    
    fpw = fopen("./out.txt", "w");
    
    for(int i = 0; i < arrayCount; i++)
    {   
        if(strcmp(arrayOfStructs[i]->type, "music") == 0 || strcmp(arrayOfStructs[i]->type, "book") == 0)
        {
            fprintf(fpw,"%s\n%s\n%s\n%s\n%s\n\n", arrayOfStructs[i]->type, arrayOfStructs[i]->name, arrayOfStructs[i]->pmt.musicBook.creator, arrayOfStructs[i]->pmt.musicBook.genre, arrayOfStructs[i]->pmt.musicBook.year);
            fflush(stdout);
        }
        else if(strcmp(arrayOfStructs[i]->type, "movie") == 0)
        {
            fprintf(fpw,"%s\n%s\n%s\n%s\n\n", arrayOfStructs[i]->type, arrayOfStructs[i]->name, arrayOfStructs[i]->pmt.Movie.rating, arrayOfStructs[i]->pmt.Movie.year);
            fflush(stdout);
        }
        else
            printf("Invalid Media Type Error");
    }
    
    fclose(fpw);
    
    for(int i = 0; i < arrayCount; i++)
    {
        if(strcmp(arrayOfStructs[i]->type, "music") == 0 || strcmp(arrayOfStructs[i]->type, "book") == 0)
        {
            free(arrayOfStructs[i]->type);
            free(arrayOfStructs[i]->name);
            free(arrayOfStructs[i]->pmt.musicBook.creator);
            free(arrayOfStructs[i]->pmt.musicBook.genre);
            free(arrayOfStructs[i]->pmt.musicBook.year);
            free(arrayOfStructs[i]);
        }
        else if(strcmp(arrayOfStructs[i]->type, "movie") == 0)
        {
            free(arrayOfStructs[i]->type);
            free(arrayOfStructs[i]->name);
            free(arrayOfStructs[i]->pmt.Movie.rating);
            free(arrayOfStructs[i]->pmt.Movie.year);
            free(arrayOfStructs[i]);
        }
    }
}

/**
 * This routine sorts the structures in the pointer array by their name in 
 * ascending order
 * 
 * routine: BubbleSort
 * 
 * return type: void
 * 
 * parameters:
 *      ptrArray[]      [struct media*]     an array of structure pointers
 *      size            [int]               the amount of structure pointers
 *                                          in the array
 * 
 * @author Brennen Calato
 * @since 2/25/2021
 */
void BubbleSort(struct media* ptrArray[], int size)
{
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(strcmp(ptrArray[i]->name, ptrArray[j]->name) > 0)
            {
                Swap(&ptrArray[i], &ptrArray[j]);
            }
        }
    }
}

/**
 * This routine is used by BubbleSort and swaps the location of two structures 
 * pointers in the array if they are out of order
 * 
 * routine: Swap
 * 
 * return type: void
 * 
 * parameters:
 *      media1      [struct media**]        a pointer to a pointer of a structure
 *                                          that is going to be swapped with the
 *                                          structure following it
 *      media2      [struct media**]        a pointer to a pointer of a structure
 *                                          that is going to be swapped with the
 *                                          structure preceding it
 * 
 * @author Brennen Calato
 * @since 2/25/21
 */
void Swap(struct media** media1, struct media** media2)
{
    //temporary storage for a structure while its address is being swapped
    struct media* temp;
    
    temp = *media1;
    *media1 = *media2;
    *media2 = temp;
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
 */
void EOLDeleter(char line[MAX_LENGTH])
{
    //a pointer to a character used to identify the location of the '\n' character and replace it with '/0'
    char* pos;
    
    while((pos=strchr(line, '\n')) != NULL)
        *pos = '\0';
}