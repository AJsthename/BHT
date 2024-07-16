#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"

sCD *First = NULL, *Last = NULL;

void insertInDList(sCD *New, int (*compare) (sCD *, sCD *)){
    sCD *tmp = First;

    if(New){
        if(First == NULL){
            First = Last = New;
        }
        else if(compare(First, New) >= 0){
            New->Next = First;
            First = First->Prev = New;
        }
        else if(compare(Last, New) <= 0){
            New->Prev = Last;
            Last = Last->Next = New;
        }
        else{
            while(tmp->Next){
                if(compare(tmp->Next, New) > 0){
                    New->Prev = tmp;
                    New->Next = tmp->Next;
                    tmp->Next = tmp->Next->Prev = New;
                    break;
                }
                tmp = tmp->Next;
            }
        }
    }
}


sCD *removeFromDList(sCD *Remove, int (*compare) (sCD *, sCD *)){
    sCD *tmp = First, *rmv = NULL;

    if(Remove){
        if(First == NULL)
            return NULL;
        else if(compare(First, Remove) == 0){
            rmv = First;
            First = First->Next;
            if(First == NULL)
                Last = NULL;
            else
                First->Prev = NULL;
        }
        else if(compare(Last, Remove) == 0){
            rmv = Last;
            Last = Last->Prev;
            Last->Next = NULL;
        }
        else{
            while(tmp->Next){
                if(compare(tmp->Next, Remove) == 0){
                    rmv = tmp->Next;
                    tmp->Next = rmv->Next;
                    tmp->Next->Prev = tmp;
                    break;
                }
                tmp = tmp->Next;
            }
        }
    }
    return rmv;
}


sCD *getFirstElement(){
    return First;
}


sCD *getLastElement(){
    return Last;
}
