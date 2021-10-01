#if !defined STDIO
#define STDIO
#endif
#if !defined STDLIB
#define STDLIB
#endif
#if !defined STRING
#define STRING
#endif
#if !defined MAX_LENGTH
#define MAX_LENGTH 100
#endif

//declaration for swap routine
void Swap(char** array1, char** array2);
//declaration for bubblesort routine
void BubbleSort(char* ptrArray[], int size);
//declaration for the end of line deleter routine
void EOLDeleter(char line[MAX_LENGTH]);


