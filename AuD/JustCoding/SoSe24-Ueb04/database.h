#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED


int save();
void saveCD(FILE *sub_Datei, sCD *CD_data);
void saveSong(FILE *sub_Datei, sSong *Song);
void userSave();
int load();
void loadCD(FILE *datei);
void loadSong(FILE *datei, sCD *CD);

/*
void loadCD(FILE *datei);
void loadSong(FILE *datei, sSong *Song);
*/

#endif // DATABASE_H_INCLUDED
