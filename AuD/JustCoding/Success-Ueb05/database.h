#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

int save();
int saveCD(FILE *datei, int selectCD);
void saveSong(FILE *datei, sCD *CD, int selectSong);
int load();
void loadCD(FILE *datei, int selectCD);
void loadSong(FILE *datei, sCD *CD, int selectSong);
#endif // DATABASE_H_INCLUDED
