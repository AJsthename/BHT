#ifndef DATETIME_H_INCLUDED
#define DATETIME_H_INCLUDED

int isLeapYear( int year);

int isDateValid(sDate date);

int getDateFromString(char date_input[20], sDate *ptr_date);

#endif // DATETIME_H_INCLUDED
