#ifndef CDS_H_INCLUDED
#define CDS_H_INCLUDED

void createCD();
void createSong(sCD *CD);

void editCD();

void deleteCD();

void searchSong();

void sortCDs();
int sort_Title(sCD *CD1, sCD *CD2);
int sort_Interpreter(sCD *CD1, sCD *CD2);
int sort_YearOfAppearance(sCD *CD1, sCD *CD2);
int sort_NumOfSongs(sCD *CD1, sCD *CD2);

void listCDs();
void listOneCD(int i);
void listOneSong(int i, int j);

#endif // CDS_H_INCLUDED
