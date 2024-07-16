#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"
#include "cds.h"

int save(){
    FILE *datei = NULL;
    sCD *Save = NULL;
    //sCD *End = NULL;

    datei = fopen("mycds_v3.xml", "w");

    if (datei == NULL){
        perror("Error opening file");
        return 0;
    }
    else{
        Save = getFirstElement();//equivalent of int i = 0;
        //End = getLastElement();

        fprintf(datei, "<Data>\n");
        while(Save != NULL){ //Loop condition
            //DEBUGGER: printf("i: %d vs countCDs: %d \n", i, countCDs);

            //DEBUGGER: fprintf(datei, " **<Title>%s</Title>**\n", CD_accs->cdTitle);

            saveCD(datei, Save);
            Save = Save->Next; //equivalent of i++;
        }
        fprintf(datei, "</Data>\n");

        fclose(datei);

        printf("\n`mycds_v3.xml` wurde erfolgreich gespeichert.\n");
        return 1;
    }

}

void saveCD(FILE *datei, sCD *saveApp){
    if (datei == NULL || saveApp == NULL){
        return;
    }

    fprintf(datei, "<CD>\n");
    fprintf(datei, " <Title>%s</Title>\n", saveApp->cdTitle);
    fprintf(datei, " <Interpret>%s</Interpret>\n", saveApp->cdInterpreter);
    fprintf(datei, " <YearOfAppearance>%d</YearOfAppearance>\n", saveApp->cdYear);

    for (int i = 0; i < saveApp->num_Of_Songs; i++){
        saveSong(datei, saveApp, i);
    }

    fprintf(datei, "</CD>\n");
}

void saveSong(FILE *datei, sCD *saveApp, int selectSong){
    if (datei == NULL || saveApp == NULL){
        return;
    }

    fprintf(datei, "    <Song>\n");
    fprintf(datei, "      <Title>%s</Title>\n", saveApp->songs[selectSong].song_Title);
    fprintf(datei, "      <Interpret>%s</Interpret>\n", saveApp->songs[selectSong].song_Interpreter? saveApp->songs[selectSong].song_Interpreter: " ");
    fprintf(datei, "      <Duration>%02d:%02d:%02d</Duration>\n", saveApp->songs[selectSong].song_Duration.hours, saveApp->songs[selectSong].song_Duration.mins, saveApp->songs[selectSong].song_Duration.secs);
    fprintf(datei, "    </Song>\n");

    return;
}

int load(){
    char zeile[101];
    char *ptrZeile;

    FILE *datei = NULL;
    sCD *Load = NULL;

    datei = fopen("mycds_v3.xml", "r");

     if (datei == NULL){
        perror("`mycds_v3.xml konnte nicht eingelesen werden\n");
        return 0;
    }
    else{
        do{
            fgets(zeile, 100, datei);
            printf("%s", zeile);

            ptrZeile = zeile;

            while((*ptrZeile == ' ') || (*ptrZeile == 9)){
            ptrZeile++;
            }
            //DEBUGGER: printf("%s\n", ptrZeile);

            if (strncmp(ptrZeile, "<CD>", 4) == 0){
                Load = malloc(sizeof(sCD));
                if(Load){
                    loadCD(datei, Load);
                    insertInDList(Load, sort_Title);
                    Load = Load->Next;
                }
            }
            if(feof(datei))
                break;

        }while(strncmp(ptrZeile, "</Data>", 7) != 0);

        fclose(datei);
        return 1;
    }
}

void loadCD(FILE *datei, sCD *loadApp){
    char zeile[101];
    char *ptrZeile;

    char *extr = NULL;
    size_t len_ot = 0, len_ct = 0, len_extr = 0;

    do{
        fgets(zeile, 100, datei);
        printf(zeile);
        ptrZeile = zeile;

        while((*ptrZeile == ' ') || (*ptrZeile == 9))
            ptrZeile++;

        if (strncmp(ptrZeile, "<Title>", 7) == 0){
           len_ot = strlen("<Title>");
           len_ct = strlen("</Title>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           loadApp->cdTitle = extr;
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           loadApp->cdInterpreter = extr;
        }

        if (strncmp(ptrZeile, "<YearOfAppearance>", 18) == 0){
           len_ot = strlen("<YearOfAppearance>");
           len_ct = strlen("</YearOfAppearance>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           loadApp->cdYear = atoi(extr);

           free(extr);
        }

        if (strncmp(ptrZeile, "<Song>", 6) == 0){
            if(loadApp->num_Of_Songs < MAXSONGS){
                loadSong(datei, loadApp, loadApp->num_Of_Songs);
                (loadApp->num_Of_Songs)++;
            }
        }
    }while(strncmp(ptrZeile, "</CD>", 5) != 0);

    return;
}

void loadSong(FILE *datei, sCD *loadApp, int selectSong){
    char zeile[101];
    char *ptrZeile;

    char *extr = NULL;
    size_t len_ot = 0, len_ct = 0, len_extr = 0;

    do{
        fgets(zeile, 100, datei);
        printf(zeile);
        ptrZeile = zeile;

        while((*ptrZeile == ' ') || (*ptrZeile == 9))
            ptrZeile++;

        if (strncmp(ptrZeile, "<Title>", 7) == 0){
           len_ot = strlen("<Title>");
           len_ct = strlen("</Title>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           loadApp->songs[selectSong].song_Title = extr;
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);

           if(extr != NULL){
                extr[len_extr] = '\0';

                loadApp->songs[selectSong].song_Interpreter = extr;
           }
        }

        if (strncmp(ptrZeile, "<Duration>", 10) == 0){
           len_ot = strlen("<Duration>");
           len_ct = strlen("</Duration>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           getTimeFromString(extr, &loadApp->songs[selectSong].song_Duration);

           free(extr);
        }
    }while(strncmp(ptrZeile, "</Song>", 7) != 0);
}

