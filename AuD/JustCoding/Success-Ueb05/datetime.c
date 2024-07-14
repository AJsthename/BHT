#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "datastructure.h"


int isLeapYear( int year){
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}


int isDateValid(sDate date){
    int daysOfMonths[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    //if the year is a leap year, then February has 29 days
    if (isLeapYear(date.Year)){

        daysOfMonths[2] = 29;
    }

    if(date.Month < 1 || date.Month > 12){
        return 0;
    }

    if(date.Day < 1 || date.Day > daysOfMonths[date.Month]){
        return 0;
    }

    return 1;
}

int getDateFromString(char date_input[20], sDate *ptr_date){
    char read[20];
    int i = 0, j = 0;
    int counter = 0;  //Initializing the date element counter to 0

    do{
        if(date_input[i] == ',' || date_input[i] == ':' || date_input[i] == '|' || date_input[i] == '/' || date_input[i] == '-'){
            char *msg = "Ungueltige Eingabe!";
            puts(msg);
            return 0;
        }
        else if(date_input[i] != '.' && date_input[i] != NULL){
            read[j] = date_input[i];
            read[j+1] = '\0';
            j++;
        }

        else{
            if(counter == 0){
                ptr_date->Day = atoi(read);
            }
            else if(counter == 1){
                ptr_date->Month = atoi(read);
            }
            else if(counter == 2){
                ptr_date->Year = atoi(read);
            }
            counter++;
            j = 0;
            read[0] = '\0';
        }

    i++;
    }while(i < 20 && counter <=2);

    return isDateValid(*ptr_date);
}

int isTimeValid(sTime Time){
    return (Time.hours >= 0 && Time.hours <= 23) &&
           (Time.mins >= 0 && Time.mins <= 59) &&
           (Time.secs >= 0 && Time.secs <= 59);
}

int getTimeFromString(char time_Input[20], sTime *ptr_time){
    char read[20] = {0};
    int i=0, j=0, counter=0, nDelimiter = 0;

    nDelimiter = countChars(time_Input, ':');
    //DEBUGGER: printf("\nNumber of Delimiters: %i", nDelimiter);

    if(nDelimiter < 2){
            counter = 1;
    }

    while(time_Input[i] != '\0' && counter <= 2 && !(nDelimiter > 2)) {
        if(time_Input[i] < '0' || time_Input[i] >= ';'){
            char *msg = "Ungueltige Eingabe!";
            puts(msg);
            return 0;
        }

        if(time_Input[i] != ':'){
            read[j] = time_Input[i];
            read[j+1] = '\0';
            j++;
        }
        else{
            if(counter == 0){
                ptr_time->hours = atoi(read);
            }
            else if(counter == 1){
                ptr_time->mins = atoi(read);
            }
            counter++;
            j = 0;
            read[0] = '\0';
        }
        i++;
    }

    if(counter == 2){
        ptr_time->secs = atoi(read);
    }

    return isTimeValid(*ptr_time);
}

int inputTime(char *prompt, sTime *ptr_time){
    char input[20];
    int check = 0;

        do{
            printf(prompt);
            printf("\n\t-> ");
            scanf("%[^\n]", input);
            clearBuffer();

            check = getTimeFromString(input, ptr_time);
        }while((check == 0) || (strlen(input) == 0));

        return 1;
}

void printTime(sTime Time, int what_Format){
    if(Time.hours == 0){
        if(what_Format == 0){
            printf("%02i:%02i", Time.mins, Time.secs);
        }
        if(what_Format == 1){
            printf("%02i:%02i:%02i", Time.hours, Time.mins, Time.secs);
        }
    }
    else{
        printf("%02i:%02i:%02i", Time.hours, Time.mins, Time.secs);
    }
    return;
}

//Vorläufiger Entwurf
sTime addTime(sSong *songs, int numOfSongs){
    sTime t_duration;
    t_duration.hours = 0;
    t_duration.mins = 0;
    t_duration.secs = 0;

    for (int i = 0; i < numOfSongs; i++) {
        t_duration.hours += songs[i].song_Duration.hours;
        t_duration.mins += songs[i].song_Duration.mins;
        t_duration.secs += songs[i].song_Duration.secs;
    }

    t_duration.mins += t_duration.secs / 60;
    t_duration.secs %= 60;

    t_duration.hours += t_duration.mins / 60;
    t_duration.mins %= 60;

    return t_duration;
}
