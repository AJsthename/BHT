#ifndef CDS_H_INCLUDED
#define CDS_H_INCLUDED

void createCD();
void createSong(sCD *CD);

void editCD();

void deleteCD();

void searchSong();

int sort_Title(sCD *CD1, sCD *CD2);
int sort_Interpreter(sCD *CD1, sCD *CD2);
int sort_YearOfAppearance(sCD *CD1, sCD *CD2);
int sort_NumOfSongs(sCD *CD1, sCD *CD2);

void listCDs();
void listCDs_Blue();
void listCDs_Red();
void listOneCD(sCD *CD_List);
void listOneSong(sCD *song_List, int i);

#endif // CDS_H_INCLUDED
