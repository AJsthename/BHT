#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED

int isLeapYear( int year);

int isDateValid(sDate date);

int getDateFromString(char date_input[20], sDate *ptr_date);

int isTimeValid(sTime Time);

int getTimeFromString(char time_Input[20], sTime *ptr_time);

int inputTime(char *prompt, sTime *ptr_time);

void printTime(sTime Time, int what_Format);
#endif // DATETIME_H_INCLUDED
