#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"


void clearScreen();
void printLine(char look, int n);
int getMenu(char *menuTitle, char *menuPoints[], int nOptions);
void clearBuffer();
ListElement *getAppend();

int main(void)
{
    ListElement *head = NULL, *prev = NULL;

    char *Title = "Element Manager";

    char *ptr1 = "Element hinzufuegen", *ptr2 = "Element und Nachfolger", *ptr3 = "Programm beenden";
    char *menuPoints[] = {ptr1, ptr2, ptr3};

    int nOptions = sizeof(menuPoints)/sizeof(menuPoints[0]);

    do{
        int choice = getMenu(Title, menuPoints, nOptions);

        switch(choice){
            case 1:
                head = getAppend(head); // head now points to the newly appended node
                printf("\nDas Element wurde eingefuegt");
                printf("List length: %d\n", length(head));
                printf("\nBitte Eingabetaste druecken ...");
                clearBuffer();
                break;

            case 2:
                removeElement(head, prev);
                head = NULL;
                printf("\nDas Element und dessen Nachfolger wurden geloescht.");
                printf("\nBitte Eingabetaste druecken ...");
                clearBuffer();
                break;

            case 3:
                printf("Programm beendet\n");
                printf("\nBitte Eingabetaste druecken ...");
                clearBuffer();
                return 0;
        }
    }while(1);

    return 0;
}

void clearScreen(){
    system("CLS");
}

void printLine(char look, int n){
    int i = 1;

    while ( i <= n){
        printf("%c", look);
        i++;
    }

    printf("\n\n");
}

int getMenu(char *menuTitle, char *menuPoints[], int nOptions){
    int choice = 0;
    int length = strlen(menuTitle) + 1;

    do{
        clearScreen();
        puts(menuTitle);
        printLine('=', length);

        int i = 0;
        for(; i < nOptions; i++){
            printf("%d. %s\n", (i + 1), menuPoints[i]);
            printf("\n");
        }

        printf("\nIhre Wahl: ");

        scanf("%d", &choice);
        clearBuffer();

    }while(choice < 1 || choice > nOptions);

    return choice;
}

void clearBuffer(){
    char Dummy;

    do{
        scanf("%c", &Dummy);
    }while (Dummy != '\n');
}

ListElement *getAppend(ListElement *head){
    float data;

    char *title = "Element einfuegen";
    puts(title);
    printLine('-', (strlen(title)+1));

    printf("Was soll der Wert des neuen Elements sein? ");
    scanf("%f", &data);
    clearBuffer();

    return appendElement(head, data);
}

