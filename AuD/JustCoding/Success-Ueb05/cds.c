#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "datetime.h"
#include "menu.h"
#include "sort.h"
#include "tools.h"
#include "cds.h"

#define VON 2000
#define BIS 2024


void createCD(){
    if(countCDs >= MAXCDS){
        printf("Maximale Anzahl von CDs erreicht.\n");
        return;
    }

    sCD *CD = &(CDData[countCDs]);
    CD->cdTitle = NULL;
    CD->cdInterpreter = NULL;
    CD->cdYear = 0;
    CD->num_Of_Songs = 0;

    printf("Erfassung einer neuen CD\n");
    printLine('-', 24);

    getText("\nGeben Sie bitte den Titel der CD ein: \n", 50, &(CD->cdTitle), 0);
    //DEBUGGER: printf("Titel: %s\n", CD->cdTitle);

    getText("\nGeben Sie bitte den Namen des Interpreten ein: \n", 50, &(CD->cdInterpreter), 1);
    //DEBUGGER: printf("Interpret: %s\n", CD->cdInterpreter);

    getNumber("\nGeben Sie bitte das Erscheinungsjahr ein: \n", &(CD->cdYear), VON, BIS);
    //DEBUGGER: printf("Erscheinungsjahr: %i\n", CD->cdYear);

    createSong(CD);

    countCDs++;
    //DEBUGGER: printf("Number of Songs: %d\n", CD->num_Of_Songs);
    waitForEnter();
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
    printf("deleteCD\n");
    waitForEnter();
    return;
}

void searchSong(){
    printf("searchSong\n");
    waitForEnter();
    return;
}
/************************************************************************************************************************************************************************************/
/*                  SORTIERVERFAHREN                                                                                                                                                */
/************************************************************************************************************************************************************************************/
void sortCDs(){
    //printf("sortCDs\n");
    int choice = 0;

    char *Title = "CDs sortieren";
    char *menuPoints[] = {"Sortieren nach CD-Titel", "Sortieren nach CD-Interpret", "Sortieren nach Erscheinungsjahr", "Sortieren nach Anzahl Lieder", "Zurueck zum Hauptmenue"};

    int nOptions = sizeof(menuPoints)/sizeof(menuPoints[0]);

    do{
        choice = getMenu(Title, menuPoints, nOptions);

        switch (choice){
            case 1:
                QuickSort(CDData, countCDs, sort_Title);
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 2:
                QuickSort(CDData, countCDs, sort_Interpreter);
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 3:
                QuickSort(CDData, countCDs, sort_YearOfAppearance);
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 4:
                QuickSort(CDData, countCDs, sort_NumOfSongs);
                printf("\nSortieren erfolgreich.");
                waitForEnter();
                break;
                //return;

            case 5:
                printf("\nZum Hauptmenue");
                printf("\n");
                waitForEnter();
                break;
        }
    }while(choice < 1 || choice > 5);

    return;
}

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
    sCD CD;

    printf("\nListe der CDs\n");
    printLine('-', 13);

    for( int i = 0; i < countCDs; i++){
        listOneCD(i);
    }

    printf("\n");
    waitForEnter();
    return;
}

void listOneCD(int i){
    int j;
    sTime t_duration;

    printf("\n\nTitel          : %s", CDData[i].cdTitle);
    printf("\nInterpret: %s", CDData[i].cdInterpreter);
    printf("\nErscheinungsjahr: %i", CDData[i].cdYear);
    printf("\nAnzahl Lieder   : %i", CDData[i].num_Of_Songs);
    printf("\nLieder");

    for(j = 0; j < CDData[i].num_Of_Songs; j++){
        listOneSong(i, j);
    }

    t_duration = addTime(CDData[i].songs, CDData[i].num_Of_Songs);

    printf("\nGesamtlaufzeit: ");
    printTime(t_duration, 1);
    //printf("\n");
}

void listOneSong(int i, int j){

    if(CDData[i].songs[j].song_Interpreter == NULL){
        printf("\n\t%02i. %s (", j+1, CDData[i].songs[j].song_Title);
    } else {
        printf("\n\t%02i. %s (%s; ", j+1, CDData[i].songs[j].song_Title, CDData[i].songs[j].song_Interpreter);
    }
    printTime(CDData[i].songs[j].song_Duration, 0);
    printf(")");

}
