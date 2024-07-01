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
        }

    i++;
    }while(i < 20 && counter <=2);

    return isDateValid(*ptr_date);
}
