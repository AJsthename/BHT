#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

ListElement *newNode(float data){
    // This is memory leak, right?
    ListElement *temp = (ListElement *) malloc(sizeof(ListElement)); //Why do we need to dynamically allocate memory here??

    if (temp == NULL){
        printf("\nSpeicherallozierung fehlgeschlagen");
        exit(1);
    }

    temp->data = data; //Value of the new node
    temp->next = NULL; //Pointer to the end of the list
    return temp; //Why do we need to return the address stored by the pointer?
}

ListElement *appendElement(ListElement *head, float valOfElem){
    //Create new node *??*
    ListElement *newListElem = newNode(valOfElem);

    //if list is empty, set the new node as the first element
    if (head == NULL){
        return newListElem;
    }
    else{
        //Traverse the list until you reach the end of the list *?*
        ListElement *curr = head;
        while (curr->next != NULL){
            curr = curr->next;
        }

        //Link the current tail to the head of the new node (list-element) *?*
        curr->next = newListElem;

        return head;
    }
}

int length(ListElement *head){
    // Initialize a counter for the length
    int length = 0;

    ListElement *curr = head;

    while (curr != NULL){
        length++;
        curr = curr->next;
    }

    return length;
}
/**YOU STOPPED HERE, ÜB0.1| Wiederholung C:
 1. Einfache und komplexe Datentypen, Schritt 4 | Date: 11.10.2024

        TO-DO:

        1) Check out if your (for) loop is correct and actually
           produces the expected result i.e. delete the chosen node
           and its successors. Correct/ Modify if necessary.

        2) Implement in the main-function (Schritt 5), then Schritt 6

        3) Do 2. Dokumentation & 3. Code-Qualität

        4) Complete and Submit
 **/

void removeElement(ListElement *head, ListElement *prev){
   if (head == NULL){
        return;
   }

   if (prev != NULL){
        prev->next = NULL; // Disconnect the previous node from its successor, since it's about to be deleted
   }

   ListElement *pNext;

   while (head != NULL){
        pNext = head->next;
        free(head);
        head = pNext;
   }
}


