#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

void swapCD(sCD *e1, sCD *e2);
int partitionCD(sCD *CD, int ui, int oi, int (*compare)(sCD *, sCD *));
void qsortCD(sCD *CD, int ui, int oi, int (*compare)(const sCD *, const sCD *));
void QuickSort(sCD *Array, int Anzahl, int (*cmpfct)(sCD *, sCD *));

#endif // SORT_H_INCLUDED
