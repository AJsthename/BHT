#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

int save();
void saveCD(FILE *sub_Datei, sCD *CD_data);
void saveSong(FILE *sub_Datei, sSong *Song);
int load();

#endif // DATABASE_H_INCLUDED
