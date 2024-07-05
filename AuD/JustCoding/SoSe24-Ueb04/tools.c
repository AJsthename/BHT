#include <stdio.h>
#include <stdlib.h>

/**********************************************************/
/**********************************************************/
void clearScreen()
{
//   system("clear"); // Linux
   system("CLS");   // Windows
}

/**********************************************************/
/**********************************************************/
void clearBuffer()
{
   char Dummy;

   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}

/**********************************************************/
/**********************************************************/
void fclearBuffer(FILE *file){
   char Dummy;

   do
   {
      fscanf(file, "%c", &Dummy);
   } while (Dummy != '\n');
   return;
}

/**********************************************************/
/**********************************************************/
void waitForEnter()
{
   printf("\nBitte Eingabetaste druecken ...");
   clearBuffer();
}

/**********************************************************/
/**********************************************************/
int askYesOrNo(char *Question)
{
   char Input;

   do
   {
      printf("%s", Question);
      scanf("%c", &Input);
      if (Input != '\n')
         clearBuffer();
   } while ((Input != 'j') && (Input != 'J') && (Input != 'n') && (Input != 'N'));
   return ((Input == 'j') || (Input == 'J'));
}
/*********************************************************/
/*********************************************************/
void printLine(char look, int howManyTimes) {
    int i = 0;
    for(;i <= howManyTimes; i++)
        printf("%c", look);

    printf("\n");

    return;
}
/*********************************************************/
/*********************************************************/
int getText(char *prompt, int maxLen,char **Text, int allowEmpty){
    char *input = NULL;
    size_t len;
    int check = 0;
    char Format[20]; //Memory allocation for format
    *Text = NULL;


    //Memory allocation for input text, maxLen+1 for '\0'(string Terminator)
    input = (char *) calloc(maxLen+1, sizeof(char));

    if (input == NULL) {
        printf("Memory allocation failed\n");
        return 0;
    }
    else {
        sprintf(Format, "%%%i[^\n]", maxLen);

        do{
            printf(prompt);
            printf("-> ");
            scanf(Format, input);
            clearBuffer();

            //Find out the length of the source string
            len = strlen(input);
            if(len > 0){
                *Text = (char *) calloc(len + 1, sizeof(char));

                if(*Text == NULL) {
                    printf("Memory allocation failed\n");
                    return 0;
                }
                else{
                    //copy the source string into the destination string
                    strcpy(*Text, input);
                    check = 1;
                }
            }
            else if(allowEmpty){
                check = 1;
            }
        }while(check != 1);

        //Free the dynamically allocated memory space
        free(input);
        return 1;
    }
}
/*********************************************************/
/*********************************************************/
int getNumber(char *prompt, int *number, int Von, int Bis){
    int input = 0;
    do{
        printf(prompt);
        printf("-> ");
        scanf("%i", &input);
        clearBuffer();

        if(input < Von || input > Bis){
            printf("Geben Sie bitte eine Zahl zwischen %i und %i ein", Von, Bis);
        }
        else{
            *number = input;
        }
    }while(input < Von || input > Bis);

    return 1;
}
/*********************************************************/
/*********************************************************/

int countChars( char str[], char c){
   int i = 0;
   int count = 0;
   for(; str[i]; i++){ // The condition str[i] is used to check for '\0' since '\0' has the value 0 which translates to FALSE, whereas all non-zero Values are considered true
        if(str[i] == c){
            count++;
        }
    }
   return count;
}
