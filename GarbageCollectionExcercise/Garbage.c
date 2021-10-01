#include <stdio.h>
#include <stdlib.h>
#define MAX_GARBAGE 7

int NumGarbage = 0;

typedef struct sCompetitor
{
    int competitorID;
    int highestScore;
    int lowestScore;
    int mostRecentScore;
}Competitor;

Competitor* GarbageCollection[MAX_GARBAGE];

void FreeStruct(Competitor* TheStruct)
{
    TheStruct->competitorID = 0;
    TheStruct->highestScore = 0;
    TheStruct->lowestScore = 0;
    TheStruct->mostRecentScore = 0;
    if(NumGarbage < 7)
    {
        GarbageCollection[NumGarbage] = (Competitor*)malloc(sizeof(Competitor));
        GarbageCollection[NumGarbage] = TheStruct;
        NumGarbage++;
    }
    else
    {
        printf("GarbageCollector full, please free or reuse memory already allocated.");
    }
}

Competitor* GetStruct()
{
    Competitor* newCompetitor;
    if(NumGarbage == 0)
    {
        newCompetitor = (Competitor*)malloc(sizeof(Competitor));
        return newCompetitor;
    }
    else
    {
        newCompetitor = GarbageCollection[NumGarbage-1];
        GarbageCollection[NumGarbage-1] = NULL;
        free(GarbageCollection[NumGarbage-1]);
        NumGarbage--;
        return newCompetitor;
    }
}

int main()
{
    Competitor competitor;
    competitor.competitorID = 57;
    printf("%d\n", competitor.competitorID);
    FreeStruct(&competitor);
    printf("%d\n", NumGarbage);
    Competitor* comp = &competitor;
    comp = GetStruct();
    printf("%d\n", NumGarbage);
    printf("%d\n", competitor.competitorID);
}

