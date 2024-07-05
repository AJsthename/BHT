#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "datastructure.h"
#include "tools.h"
#include "cds.h"
#include "datetime.h"
#include "database.h"


int main()
{
    char *Title = "CD-Verwaltung Deluxe";

    //Defining pointers to strings that will be used in array of pointers to strings *menuPoints[]
    char *ptr1 = "Neue CD anlegen",*ptr2 = "CD bearbeiten", *ptr3 = "CD loeschen", *ptr4 = "Suchen", *ptr5 = "Sortieren", *ptr6 = "Auflisten", *ptr7 = "Programm beenden";
    char *menuPoints[] = {ptr1, ptr2, ptr3, ptr4, ptr5, ptr6, ptr7};

    //Determine the number of elements within the array
    int nOptions = sizeof(menuPoints)/sizeof(menuPoints[0]);

    load();
    do{
            int choice = getMenu(Title, menuPoints, nOptions);

            switch (choice){
                case 1:
                    createCD();
                    break;

                case 2:
                    editCD();
                    break;

                case 3:
                    deleteCD();
                    break;

                case 4:
                    searchSong();
                    break;

                case 5:
                    sortCDs();
                    break;

                case 6:
                    listCDs();
                    break;

                case 7:
                    userSave();
                    printf("\nProgramm beendet\n");
                    waitForEnter();
                    return 0;
            }
    }while(1);

    return 0;
}
