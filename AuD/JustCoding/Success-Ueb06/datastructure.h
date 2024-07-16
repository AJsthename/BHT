#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAXSONGS 30
//#define MAXCDS 100

typedef struct {
    int Day;
    int Month;
    int Year;
}sDate;

typedef struct {
    int hours;
    int mins;
    int secs;
}sTime;

typedef struct {
    char *song_Title;
    char *song_Interpreter;
    sTime song_Duration;
}sSong;

typedef struct sCDLE{
    char *cdTitle;
    char *cdInterpreter;
    int cdYear;
    int num_Of_Songs;
    struct sCDLE *Next;
    struct sCDLE *Prev;
    sSong songs[MAXSONGS];
    int ID;
}sCD;

//extern int countCDs;
extern sCD *First, *Last;

#endif // DATASTRUCTURE_H_INCLUDED
