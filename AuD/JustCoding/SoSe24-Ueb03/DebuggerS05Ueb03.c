#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int hours;
    int mins;
    int secs;
}sTime;

void clearBuffer();
int isTimeValid(sTime Time);
int getTimeFromString(char time_Input[20], sTime *ptr_time);
int inputTime(char *prompt, sTime *ptr_time);

int main(void){
    sTime *debug_Duration = (sTime *) calloc(1, sizeof(sTime));

    if(debug_Duration == NULL){
        printf("Memory allocation failed\n");
        return 1;
    }

    inputTime("\nGeben Sie bitte eine Dauer ein: ", debug_Duration);
    printf("\nStunde: %i", debug_Duration->hours);
    printf("\nMinuten: %i", debug_Duration->mins);
    printf("\nSekunden: %i", debug_Duration->secs);

    free(debug_Duration);
    return 0;
}

int isTimeValid(sTime Time){
    return (Time.hours >= 0 && Time.hours <= 23) &&
           (Time.mins >= 0 && Time.mins <= 59) &&
           (Time.secs >= 0 && Time.secs <= 59);
}

int getTimeFromString(char time_Input[20], sTime *ptr_time){
    char read[20] = {0};
    int i=0, j=0, counter=0;

    while(time_Input[i] != '\0' && counter <= 2) {
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
    //size_t length_Of_String;

        do{
            printf(prompt);
            scanf("%19[^\n]", input);
            clearBuffer();
            //length_Of_String = strlen(input);

            check = getTimeFromString(input, ptr_time);
        }while((check == 0) || (strlen(input) == 0));

        return 1;
}

void clearBuffer()
{
   char Dummy;

   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}
