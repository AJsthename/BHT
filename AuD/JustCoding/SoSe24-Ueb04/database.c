#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"
#include "cds.h"
#include "database.h"

int save(){
        FILE *datei = fopen("mycds.xml", "w");
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

        printf("Datei `mycds.xml` wurde wahrscheinlich erstellt oder überschrieben");
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

int load(){
    char zeile[101];
    char *ptrZeile;

    FILE *datei = fopen("mycds.xml", "r");
    if (datei == NULL){
        perror("Error opening file\n");
        return 0;
    }
    else
    do{
        fscanf(datei, "%100[^\n]", zeile);
        fclearBuffer(datei);
        ptrZeile = zeile;

        while((*ptrZeile == ' ') || (*ptrZeile == 9)) // 9 ist der ASCII-Wert eines Tabs
            ptrZeile++;
        if (strncmp(ptrZeile, "<CD>", 4) == 0){
            if (countCDs < MAXCDS){
                //loadCD();
                //countCDs++;
            }
        }
        if (feof(datei))
            break;
    }while(strncmp(ptrZeile, "</Data>", 7) != 0);

    fclose(datei);
    return 1;
}

void loadCD(){

    return;
}

void loadSong(){

    return;
}




