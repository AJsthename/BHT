#include <stdio.h>
#include <stdlib.h>

void saveData(FILE *file);

int main() {
    FILE *datei = fopen("employees.txt", "w");
    if (datei == NULL) {
        perror("Error opening file");
        return 0;
    }

    fprintf(datei, "<Data>\n");
    saveData(datei);
    fprintf(datei, "</Data>\n");

    fclose(datei);
    printf("File 'employees.txt' should have been created or overwritten.\n");

    return 1;
}

void saveData(FILE *file){
    char *name = "Anna";
    int emp_num = 1001;

    fprintf(file, " <Employee>\n");
    fprintf(file, "   <Name>%s</Name>\n", name);
    fprintf(file, "   <Number>%d</Number>\n", emp_num);
    fprintf(file, " </Employee>\n");

    return;
}
