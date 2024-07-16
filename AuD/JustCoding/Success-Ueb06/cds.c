#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "menu.h"
#include "sort.h"
#include "tools.h"
#include "cds.h"
#include "database.h"

#define VON 2000
#define BIS 2024


void createCD(){
    int check = 0;

    //Initializing Linked list for further iteration, this is the equivalent of int i = 0
    sCD *CD_block = malloc(sizeof(sCD));

    if(CD_block != NULL ){
        //WICHTIG!!!
        CD_block->cdTitle = NULL;
        CD_block->cdInterpreter = NULL;
        CD_block->cdYear = 0;
        CD_block->num_Of_Songs = 0;
        CD_block->Next = NULL;
        CD_block->Prev = NULL;

        printf("Erfassung einer neuen CD\n");
        printLine('-', 24);

        getText("\nGeben Sie bitte den Titel der CD ein: \n", 100, &(CD_block->cdTitle), 0);
        //DEBUGGER: printf("Titel: %s\n", CD_block->cdTitle);

        getText("\nGeben Sie bitte den Namen des Interpreten ein: \n", 100, &(CD_block->cdInterpreter), 1);
        //DEBUGGER: printf("Interpret: %s\n", CD_block->cdInterpreter);

        getNumber("\nGeben Sie bitte das Erscheinungsjahr ein: \n", &(CD_block->cdYear), VON, BIS);
        //DEBUGGER: printf("Erscheinungsjahr: %i\n", CD_block->cdYear);

        createSong(CD_block);



        check = 1;
    }

    if(check == 1){
        insertInDList(CD_block, sort_Title);
        waitForEnter();
    }

    //countCDs++;
    //DEBUGGER: printf("Number of Songs: %d\n", CD->num_Of_Songs);
    return;
}

void createSong(sCD *CD){
    int answer = 0;

    do {
        sSong *Song = &(CD->songs[CD->num_Of_Songs]);
        Song->song_Title = NULL;
        Song->song_Interpreter = NULL;
        Song->song_Duration.hours = 0;
        Song->song_Duration.mins = 0;
        Song->song_Duration.secs = 0;

        printf("\n\tLied %i:", (CD->num_Of_Songs)+1);

        getText("\n\tGeben Sie bitte den Titel des Liedes ein: \n\t", 50, &(Song->song_Title), 0);
        //DEBUGGER: printf("Titel: %s\n", Song->song_Title);

        getText("\n\tGeben Sie bitte den Interpreten ein: \n\t", 50, &(Song->song_Interpreter), 1);
        //DEBUGGER: printf("Interpreter: %s\n", Song->song_Interpreter);

        inputTime("\n\tGeben Sie bitte die Dauer des Liedes ein: ", &(Song->song_Duration));
        //DEBUGGER: printf("\nDauer: %02i:%02i:%02i\n", Song->song_Duration.hours, Song->song_Duration.mins, Song->song_Duration.secs);

        (CD->num_Of_Songs)++;

        if(CD->num_Of_Songs >= MAXSONGS){
            printf("Maximale Anzahl von Liedern erreicht.\n");
            break;
        }

        answer = askYesOrNo("\nMoechten Sie noch ein weiteres Lied eingeben (j/n)? ");
    } while(answer == 1); //&& CD->num_Of_Songs < MAXSONGS);

    return;
}

void editCD(){
    printf("editCD\n");
    waitForEnter();
    return;
}

void deleteCD(){
    sCD *Delete = NULL;
    int i = 0;
    int choice;

    Delete = getFirstElement();

    printf("\nListe der CDs\n");
    printLine('-', 13);
    printf("\n");

    while(Delete != NULL){
        Delete->ID = ++i;
        printf("%i: %s\n", i, Delete->cdTitle);
        Delete = Delete->Next;
    }
    do{
        printf("\nWelche CD moechten Sie loeschen (0 fuer Abbrechen) ? ");
        scanf("%i", &choice);
        clearBuffer();
    }while(choice < 0 || choice >= i);


    if(choice != 0){
        Delete = getFirstElement(); //Reset the pointer to the first element

        while(Delete != NULL){
            if(Delete->ID == choice){
                sCD *cdToRemove = removeFromDList(Delete, sort_Title);
                free(cdToRemove);
                //save();
                printf("CD wurde erfolgreich geloescht.\n");
                break;
            }
            Delete = Delete->Next;
        }
    }
    waitForEnter();
    return;
}

void searchSong(){
    printf("searchSong\n");
    waitForEnter();
    return;
}
/************************************************************************************************************************************************************************************/
/*                  VERGLEICHSFUNKTIONEN                                                                                                                                               */
/************************************************************************************************************************************************************************************/

int sort_Title(sCD *CD1, sCD *CD2){
    return strcmp(CD1->cdTitle, CD2->cdTitle);
}

int sort_Interpreter(sCD *CD1, sCD *CD2){
    if (CD1->cdInterpreter == CD2->cdInterpreter)
        return 0;
    else if (CD1->cdInterpreter == NULL)
        return 1;
    else if (CD2->cdInterpreter == NULL)
        return -1;
    else
        return strcmp(CD1->cdInterpreter, CD2->cdInterpreter);
}

int sort_YearOfAppearance(sCD *CD1, sCD *CD2){
    if ((CD1->cdYear - CD2->cdYear) == 0)
        return 0;
    else
        return CD1->cdYear - CD2->cdYear;
}

int sort_NumOfSongs(sCD *CD1, sCD *CD2){
    if ((CD1->num_Of_Songs - CD2->num_Of_Songs) == 0)
        return 0;
    else
        return CD1->num_Of_Songs - CD2->num_Of_Songs;
}
/************************************************************************************************************************************************************************************/
/************************************************************************************************************************************************************************************/

void listCDs(){
    int choice = 0;

    char *Title = "CDs auflisten";
    char *menuPoints[] = {"Ausgabe nach CD-Titel aufwaerts sortiert", "Ausgabe nach CD-Titel abwaerts sortiert", "Zurueck zum Hauptmenue"};

    int nOptions = sizeof(menuPoints)/sizeof(menuPoints[0]);

    do{
        choice = getMenu(Title, menuPoints, nOptions);

        switch (choice){
            case 1:
                listCDs_Blue();
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 2:
                listCDs_Red();
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 3:
                printf("\nZum Hauptmenue");
                printf("\n");
                waitForEnter();
                break;
        }
    }while(choice < 1 || choice > 3);

    return;
}

void listCDs_Blue(){
    sCD *CD_List = NULL;

    CD_List = getFirstElement();

    printf("\nListe der CDs\n");
    printLine('-', 13);

    while(CD_List){
        listOneCD(CD_List);
        CD_List = CD_List->Next;
    }

    printf("\n");
    waitForEnter();
    return;
}

void listCDs_Red(){
    sCD *CD_List = NULL;

    CD_List = getLastElement();

    printf("\nListe der CDs\n");
    printLine('-', 13);

    while(CD_List){
        listOneCD(CD_List);
        CD_List = CD_List->Prev;
    }

    printf("\n");
    waitForEnter();
    return;
}

void listOneCD(sCD *CD_List){
    int i;
    sTime t_duration;

    if (CD_List == NULL){
        return;
    }

    printf("\n\nTitel          : %s", CD_List->cdTitle);
    printf("\nInterpret: %s", CD_List->cdInterpreter);
    printf("\nErscheinungsjahr: %i", CD_List->cdYear);
    printf("\nAnzahl Lieder   : %i", CD_List->num_Of_Songs);
    printf("\nLieder");

    for(i = 0; i < CD_List->num_Of_Songs; i++){
        listOneSong(CD_List, i);
    }

    t_duration = addTime(CD_List->songs, CD_List->num_Of_Songs);

    printf("\nGesamtlaufzeit: ");
    printTime(t_duration, 1);
    //printf("\n");
}

void listOneSong(sCD *song_List, int i){

    if(song_List->songs[i].song_Interpreter == NULL){
        printf("\n\t%02i. %s (", i+1, song_List->songs[i].song_Title);
    } else {
        printf("\n\t%02i. %s (%s; ", i+1, song_List->songs[i].song_Title, song_List->songs[i].song_Interpreter);
    }
    printTime(song_List->songs[i].song_Duration, 0);
    printf(")");

}

