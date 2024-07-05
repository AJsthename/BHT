#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"
#include "cds.h"
#include "database.h"

int save(){
        FILE *datei = fopen("mycds.xml", "wb");
        if (datei == NULL){
            perror("Error opening file");
            return 0;
        }
        else
            fprintf(datei, "<Data>\n");
            for (int i = 0; i < countCDs; i++){ //countCDs
                saveCD(datei, &CDData[i]);
            }
            fprintf(datei, "</Data>\n");

            fclose(datei);

        printf("\n`mycds.xml` wurde erfolgreich gespeichert.\n");
        return 1;
}

void saveCD(FILE *sub_Datei, sCD *CD_data){
    fprintf(sub_Datei, "<CD>\n");

    fprintf(sub_Datei, " <Title>%s</Title>\n", CD_data->cdTitle);
    fprintf(sub_Datei, " <Interpret>%s</Interpret>\n", CD_data->cdInterpreter);
    fprintf(sub_Datei, " <YearOfAppearance>%d</YearOfAppearance>\n", CD_data->cdYear);
    for (int i = 0; i < CD_data->num_Of_Songs; i++){
        saveSong(sub_Datei, &CD_data->songs[i]);
    }

    fprintf(sub_Datei, "</CD>\n");
    return;
}

void saveSong(FILE *sub_Datei, sSong *Song){
    fprintf(sub_Datei, "    <Song>\n");
    fprintf(sub_Datei, "      <Title>%s</Title>\n", Song->song_Title);
    fprintf(sub_Datei, "      <Interpret>%s</Interpret>\n", Song->song_Interpreter);
    fprintf(sub_Datei, "      <Duration>%02d:%02d:%02d</Duration>\n", Song->song_Duration.hours, Song->song_Duration.mins, Song->song_Duration.secs);
    fprintf(sub_Datei, "    </Song>\n");
    return;
}

void userSave(){
    int answer = 0;
    int checkSave = 0;

    do{
        answer = askYesOrNo("\nWollen Sie Ihre Aenderungen speichern? ");

        if (answer){
            checkSave = save();
            if (!(checkSave))
                perror("Speichern fehlgeschlagen! Versuchen Sie bitte noch einmal\n");
        }
    }while(checkSave == 0);


    return ;
}

int load(){
    char zeile[101];
    char *ptrZeile;

    FILE *datei = NULL;
    datei = fopen("mycds.xml", "r");

    if (datei == NULL){
        perror("`mycds.xml konnte nicht eingelesen werden\n");
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
            //printf("%s\n", ptrZeile);

            if (strncmp(ptrZeile, "<CD>", 4) == 0){
                if(countCDs < MAXCDS){
                    loadCD(datei);
                    countCDs++;
                }
            }
            if(feof(datei))
                break;

        }while(strncmp(ptrZeile, "</Data>", 7) != 0);

        fclose(datei);
        return 1;
    }
}

void loadCD(FILE *datei){
    char zeile[101];
    char *ptrZeile;

    char *extr = NULL;
    size_t len_ot = 0, len_ct = 0, len_extr = 0;

    sCD *CD = &CDData[countCDs];

    do {
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

           //printf("**** %s ****\n", extr);

           CD->cdTitle = extr;

           printf("같같 %s 같같\n", CD->cdTitle);
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           //printf("**** %s ****\n", extr);

           CD->cdInterpreter = extr;

           printf("같같 %s 같같\n", CD->cdInterpreter);
        }

        if (strncmp(ptrZeile, "<YearOfAppearance>", 18) == 0){
           len_ot = strlen("<YearOfAppearance>");
           len_ct = strlen("</YearOfAppearance>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           //printf("**** %s ****\n", extr);

           CD->cdYear = atoi(extr);

           printf("같같 %d 같같\n", CD->cdYear);

           free(extr);
        }

        if (strncmp(ptrZeile, "<Song>", 6) == 0){
            loadSong(datei, CD);
        }
    }while(strncmp(ptrZeile, "</CD>", 5) != 0);
}

void loadSong(FILE *datei, sCD *CD){
    char zeile[101];
    char *ptrZeile;

    char *extr = NULL;
    size_t len_ot = 0, len_ct = 0, len_extr = 0;

    sSong *Song = &CD->songs[CD->num_Of_Songs];

    do {
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

           //printf("**** %s ****\n", extr);

           Song->song_Title = extr;

           printf("같같 %s 같같\n", Song->song_Title);
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           //printf("**** %s ****\n", extr);

           Song->song_Interpreter = extr;

           printf("같같 %s 같같\n", Song->song_Interpreter);
        }

        if (strncmp(ptrZeile, "<Duration>", 10) == 0){
           len_ot = strlen("<Duration>");
           len_ct = strlen("</Duration>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           //printf("**** %s ****\n", extr);

           getTimeFromString(extr, &Song->song_Duration);

           printf("같같 %02d:%02d:%02d 같같\n", Song->song_Duration.hours, Song->song_Duration.mins, Song->song_Duration.secs);

           free(extr);
        }

        CD->num_Of_Songs++;
    }while(strncmp(ptrZeile, "</Song>", 7) != 0);
}
