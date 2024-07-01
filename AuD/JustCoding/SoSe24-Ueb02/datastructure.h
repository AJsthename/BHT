#ifndef DATASTRUCTURE_H_INCLUDED
#define DATASTRUCTURE_H_INCLUDED

#define MAXSONGS 30
#define MAXCDS 100

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
    char *sTitle;
    char *sInterpreter;
    sTime duration;
}sSong;

typedef struct {
    char *cdTitle;
    char *cdInterpreter;
    int cdYear;
    int num_Of_Songs;
    sSong songList[MAXSONGS];
}sCD;

extern int countCDs;
extern sCD CDData[];

#endif // DATASTRUCTURE_H_INCLUDED
