#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

void clearBuffer();
void fclearBuffer(FILE *file);
void clearScreen();
void waitForEnter();
int askYesOrNo(char *Question);
void enter(int howManyTimes);
void printLine(char look, int howManyTimes);
int getText(char *prompt, int maxLen,char **Text, int allowEmpty);
int getNumber(char *prompt, int *number, int Von, int Bis);
int countChars( char str[], char c);

#endif // TOOLS_H_INCLUDED
