#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"
#include "cds.h"

int save(){
    FILE *datei = fopen("mycds_v3.xml", "w");
    if (datei == NULL){
        perror("Error opening file");
        return 0;
    }
    else{
        fprintf(datei, "<Data>\n");
        for (int i = 0; i <= countCDs; i++){
            //DEBUGGER: printf("i: %d vs countCDs: %d \n", i, countCDs);

            //DEBUGGER: fprintf(datei, " **<Title>%s</Title>**\n", CD_accs->cdTitle);

            saveCD(datei, i);
        }
        fprintf(datei, "</Data>\n");

        fclose(datei);

        printf("\n`mycds_v3.xml` wurde erfolgreich gespeichert.\n");
        return 1;
    }

}

int saveCD(FILE *datei, int selectCD){
    if (CDData[selectCD].cdTitle == NULL){
        return 0;
    }

    fprintf(datei, "<CD>\n");
    fprintf(datei, " <Title>%s</Title>\n", CDData[selectCD].cdTitle);
    fprintf(datei, " <Interpret>%s</Interpret>\n", CDData[selectCD].cdInterpreter);
    fprintf(datei, " <YearOfAppearance>%d</YearOfAppearance>\n", CDData[selectCD].cdYear);

    for (int j = 0; j < CDData[selectCD].num_Of_Songs; j++){
        saveSong(datei, &CDData[selectCD], j);
    }

    fprintf(datei, "</CD>\n");
    return 1;
}

void saveSong(FILE *datei, sCD *CD, int selectSong){
        fprintf(datei, "    <Song>\n");
        fprintf(datei, "      <Title>%s</Title>\n", CD->songs[selectSong].song_Title);
        fprintf(datei, "      <Interpret>%s</Interpret>\n", CD->songs[selectSong].song_Interpreter? CD->songs[selectSong].song_Interpreter: " ");
        fprintf(datei, "      <Duration>%02d:%02d:%02d</Duration>\n", CD->songs[selectSong].song_Duration.hours, CD->songs[selectSong].song_Duration.mins, CD->songs[selectSong].song_Duration.secs);
        fprintf(datei, "    </Song>\n");

    return;
}

int load(){
    char zeile[101];
    char *ptrZeile;

    FILE *datei = NULL;
    datei = fopen("mycds_v3.xml", "r");

     if (datei == NULL){
        perror("`mycds_v3.xml konnte nicht eingelesen werden\n");
        return 0;
    }
    else{
        do{
            fgets(zeile, 100, datei);
            //fclearBuffer(datei);
            printf("%s", zeile);

            ptrZeile = zeile;

            while((*ptrZeile == ' ') || (*ptrZeile == 9)){
            ptrZeile++;
            }
            //DEBUGGER: printf("%s\n", ptrZeile);

            if (strncmp(ptrZeile, "<CD>", 4) == 0){
                if(countCDs < MAXCDS){
                    //DEBUGGER: printf("***CD number %d***\n", countCDs);
                    loadCD(datei, countCDs);
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

void loadCD(FILE *datei, int selectCD){
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

           CDData[selectCD].cdTitle = extr;
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           CDData[selectCD].cdInterpreter = extr;
        }

        if (strncmp(ptrZeile, "<YearOfAppearance>", 18) == 0){
           len_ot = strlen("<YearOfAppearance>");
           len_ct = strlen("</YearOfAppearance>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           CDData[selectCD].cdYear = atoi(extr);

           free(extr);
        }

        if (strncmp(ptrZeile, "<Song>", 6) == 0){
            if(CDData[selectCD].num_Of_Songs < MAXSONGS){
                loadSong(datei, &CDData[selectCD], CDData[selectCD].num_Of_Songs);
                (CDData[selectCD].num_Of_Songs)++;
            }
        }
    }while(strncmp(ptrZeile, "</CD>", 5) != 0);

    return;
}

void loadSong(FILE *datei, sCD *CD, int selectSong){
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

           CD->songs[selectSong].song_Title = extr;
        }

        if (strncmp(ptrZeile, "<Interpret>", 11) == 0){
           len_ot = strlen("<Interpret>");
           len_ct = strlen("</Interpret>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);

           if(extr != NULL){
                extr[len_extr] = '\0';

                CD->songs[selectSong].song_Interpreter = extr;
           }
        }

        if (strncmp(ptrZeile, "<Duration>", 10) == 0){
           len_ot = strlen("<Duration>");
           len_ct = strlen("</Duration>");

           len_extr = strlen(ptrZeile) - len_ot - len_ct -1;
           extr = (char *) calloc(len_extr+1, sizeof(char));

           strncpy(extr, ptrZeile+len_ot, len_extr);
           extr[len_extr] = '\0';

           getTimeFromString(extr, &CD->songs[selectSong].song_Duration);

           free(extr);
        }
    }while(strncmp(ptrZeile, "</Song>", 7) != 0);
}
