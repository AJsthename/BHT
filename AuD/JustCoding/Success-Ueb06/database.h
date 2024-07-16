#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

int save();
void saveCD(FILE *datei, sCD *saveApp);
void saveSong(FILE *datei, sCD *saveApp, int selectSong);
int load();
void loadCD(FILE *datei, sCD *loadApp);
void loadSong(FILE *datei, sCD *loadApp, int selectSong);
#endif // DATABASE_H_INCLUDED
