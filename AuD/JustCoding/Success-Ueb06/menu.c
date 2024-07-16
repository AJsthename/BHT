#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "datastructure.h"

int getMenu(char *menuTitle, char *menuPoints[], int nOptions){
    int choice = 0;
    do{
        //clearScreen();
        printf("%s\n", menuTitle);
        printLine('=', 21);
        printf("\n");

        int i = 0;
        for(; i < nOptions; i++)
            printf("%d. %s\n",(i + 1), menuPoints[i]);
            printf("\n");

            printf("Ihre Wahl: ");

            scanf("%d", &choice);
            clearBuffer();

    }while(choice < 1 || choice > nOptions);

    return choice;
}
