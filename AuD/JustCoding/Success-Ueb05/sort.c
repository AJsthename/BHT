#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "tools.h"

void swapCD(sCD *e1, sCD *e2){
    sCD temp;

    // Copy the titles
    temp.cdTitle = e1->cdTitle;
    e1->cdTitle = e2->cdTitle;
    e2->cdTitle = temp.cdTitle;

    // Copy the interpreters
    temp.cdInterpreter = e1->cdInterpreter;
    e1->cdInterpreter = e2->cdInterpreter;
    e2->cdInterpreter = temp.cdInterpreter;

    // Copy the year of appearance
    temp.cdYear = e1->cdYear;
    e1->cdYear = e2->cdYear;
    e2->cdYear = temp.cdYear;

    // Copy the number of songs
    temp.num_Of_Songs = e1->num_Of_Songs;
    e1->num_Of_Songs = e2->num_Of_Songs;
    e2->num_Of_Songs = temp.num_Of_Songs;

    // Copy the songs array
    for (int i = 0; i < MAXSONGS; i++) {
        temp.songs[i] = e1->songs[i];
        e1->songs[i] = e2->songs[i];
        e2->songs[i] = temp.songs[i];
    }
}

int partitionCD(sCD *CD, int ui, int oi, int (*compare)(sCD *, sCD *)){
    sCD *comp = CD + ui;
    int i = ui, j = oi;
    while (i <= j){
        while ( (i <= j) && (compare(CD + i, comp) <= 0) )
            i++;
        while ( (j >= i) && (compare(CD + j, comp) >= 0) )
            j--;
        if (i < j){
            swapCD(CD + i, CD + j);
            i++;
            j--;
        }
    }
    i--;
    swapCD(comp, CD + j);

    return i;
}

void qsortCD(sCD *CD, int ui, int oi, int (*compare)(const sCD *,const sCD *)){
    int idx;

    if (ui >= oi) //Abbruchsbedingung von Rekursion
        return;
    else
    {
        idx = partitionCD(CD, ui, oi, compare);
        qsortCD(CD, ui, idx - 1, compare);
        qsortCD(CD, idx + 1, oi, compare);
    }
}

void QuickSort(sCD *Array, int Anzahl, int (*cmpfct)(sCD *, sCD *)){
    qsortCD(Array, 0, Anzahl - 1, cmpfct);
}
