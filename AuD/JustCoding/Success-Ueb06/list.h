#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
#include "datastructure.h"

void insertInDList(sCD *New, int (*compare) (sCD *, sCD *));

sCD *removeFromDList(sCD *Remove, int (*compare) (sCD *, sCD *));

sCD *getFirstElement();

sCD *getLastElement();

#endif // LIST_H_INCLUDED
