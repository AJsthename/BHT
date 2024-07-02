#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "menu.h"

int countCDs = 0;
sCD CDData[MAXCDS];

void createCD(){
    if(countCDs >= MAXCDS){
        printf("Maximale Anzahl von CDs erreicht.\n");
        return;
    }

    sCD *CD = &(CDData[countCDs]); //assign the memory address'countCDs'-th element
                                 //of the array CDData to the pointer variable CD
                                 //In this way all the CDs we generate are safely stored
                                 //until the maximum limit is attained

    //Initializing the elements of sCD-Structure
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

    getNumber("\nGeben Sie bitte das Erscheinungsjahr ein: \n", &(CD->cdYear), 2000, 2024);
    //DEBUGGER: printf("Erscheinungsjahr: %i\n", CD->cdYear);

    createSong(CD);

    countCDs++;
    waitForEnter();

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

void sortCDs(){
    printf("sortCDs\n");
    waitForEnter();
    return;
}

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

void createSong(sCD *CD){
    if(CD->num_Of_Songs >= MAXSONGS){
        printf("Maximale Anzahl von Liedern erreicht.\n");
        return;
    }


    int answer = 0;

    printf("\nGeben Sie bitte die Daten der Lieder ein: ");

    do{
        sSong *Song = &(CD->songs[CD->num_Of_Songs]);

        Song->song_Title = NULL;
        Song->song_Interpreter = NULL;

        Song->song_Duration.hours = 0;
        Song->song_Duration.mins = 0;
        Song->song_Duration.secs = 0;

        printf("\n\n\tLied %i:", (CD->num_Of_Songs)+1);

        getText("\n\tGeben Sie bitte den Titel des Liedes ein: \n\t", 50, &(Song->song_Title), 0);
        //DEBUGGER: printf("Titel: %s\n", Song->song_Title);
        getText("\n\tGeben Sie bitte den Interpreten ein: \n\t", 50, &(Song->song_Interpreter), 1);
        //DEBUGGER: printf("Interpreter: %s\n", Song->song_Interpreter);
        inputTime("\n\tGeben Sie bitte die Dauer des Liedes ein: ", &(Song->song_Duration));

        //DEBUGGER: printf("\nDauer: %02i:%02i:%02i\n", Song->song_Duration.hours, Song->song_Duration.mins, Song->song_Duration.secs);


        (CD->num_Of_Songs)++;
        //DEBUGGER: printf("\nNumber of Songs: %i", CD->num_Of_Songs);

        answer = askYesOrNo("\nMoechten Sie noch ein weiteres Lied eingeben (j/n)? ");

    }while(answer == 1 && CD->num_Of_Songs < MAXSONGS);

    return;
}

void listOneCD(int i){
    int j;

    printf("\n\nTitel          : %s", CDData[i].cdTitle);
    printf("\nErscheinungsjahr: %i", CDData[i].cdYear);
    printf("\nAnzahl Lieder   : %i", CDData[i].num_Of_Songs);
    printf("\nLieder");

    for(j = 0; j < CDData[i].num_Of_Songs; j++){
        listOneSong(i, j);
    }

    return;
}

void listOneSong(int i, int j){
    if(CDData[i].songs[j].song_Interpreter == NULL){
        printf("\n\t%02i. %s (", j+1, CDData[i].songs[j].song_Title);
    }
    else{
        printf("\n\t%02i. %s (%s; ", j+1, CDData[i].songs[j].song_Title, CDData[i].songs[j].song_Interpreter);
    }
    printTime(CDData[i].songs[j].song_Duration, 0);
    printf(")");
    return;
}
