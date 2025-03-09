#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "declares.h"

#define MAXLINE 128
void readstudent(FILE *input, FILE *output) {
    char line[MAXLINE];
    student st;

    fgets(line, sizeof(line), input); // Пропускаем заголовок

    while (fgets(line, MAXLINE, input)) {

        char *token = strtok(line, ";"); // Разбиваем строку на токены

        strcpy(st.surname, token);
        token = strtok(NULL, ";");
        strcpy(st.initials, token);
        token = strtok(NULL, ";");
        strcpy(st.gender, token);
        token = strtok(NULL, ";");
        st.schoolNum = atoi(token);
        token = strtok(NULL, ";");
        strcpy(st.medal, token);
        token = strtok(NULL, ";");
        st.maths = atoi(token);
        token = strtok(NULL, ";");
        st.russian = atoi(token);
        token = strtok(NULL, ";");
        st.informatics = (strcmp(token, "-") == 0) ? 0 : atoi(token);
        token = strtok(NULL, ";");
        st.physics = (strcmp(token, "-") == 0) ? 0 : atoi(token);
        token = strtok(NULL, ";");
        strcpy(st.essay, token);
        token = strtok(NULL, ";");
        st.total = atoi(token);

        if (fwrite(&st, sizeof(st), 1, output) != 1) {
            perror("Ошибка записи в файл");
            return;
        }
    }
}

int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");
    if (argc != 3) {
        printf("Usage: %s inputfile outputfile\n", argv[0]);
    }

    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "wb");
    if (!input || !output) {
        perror("Ошибка открытия файла");
        return 1;
    }
    readstudent(input, output);
    fclose(input);
    fclose(output);
    return 0;
}
