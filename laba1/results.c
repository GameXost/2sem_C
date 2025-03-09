//
// Created by GameXost on 23.02.2025.
//

#include <math.h>
#include <stdio.h>
#include <string.h>
#include "declares.h"


void table(student st) {
    {
        int num = 11 - (int) strlen(st.surname) / 2;
        int num2 = 3 - ((int) log10(st.schoolNum) + 1);
        int num3 = 5 - ((int) log10(st.maths) + 1);
        int num4 = 5 - ((int) log10(st.russian) + 1);
        int num5 = st.informatics > 0 ? 5 - ((int) log10(st.informatics) + 1) : 4;
        int num6 = st.physics > 0 ? 5 - ((int) log10(st.physics) + 1) : 4;
        int num7 = 5 - ((int) log10(st.total) + 1);
        int num8 = 5 - (int) strlen(st.medal) / 2;
        int num_1 = 7 - (int) strlen(st.essay) / 2;
        
        printf("|%*s%s%*s| %s |  %s  |%*s%d%*s|%*s%s%*s|%*s%d%*s|%*s%d%*s|%*s%d%*s|%*s%d%*s|%*s%s%*s|%*s%d%*s|\n", 3,
               "", st.surname, num, "", st.initials, st.gender, 1, "", st.schoolNum, num2, "", 3, "", st.medal, num8,
               "", 2, "", st.maths, num3, "", 3, "", st.russian, num4, "", 3, "", st.informatics, num5, "", 3, "",
               st.physics, num6, "", 2, "", st.essay, num_1, "", 2, "", st.total, num7, "");
        printf("------------------------------------------------------------------------------------------------\n");
    }
}


void inp(FILE *database, int flag) {
    student st;
    printf("|   Фамилия    | И.О. | М/Ж | шк | медаль | матем | рус.яз | инф-ка | физ-ка | сочин-е | сумма |\n");
    printf("------------------------------------------------------------------------------------------------\n");
    if (flag == 1) {
        while (fread(&st, sizeof(st), 1, database)) {
            if (strcmp(st.medal, "Да") == 0 && st.maths <= 60) {

                table(st);
            }
        }
        printf("Математика завалена, но есть медаль");

    } else {
        while (fread(&st, sizeof(st), 1, database)) {
            table(st);
        }
    }
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("ooops, wrong input\n");
    }
    FILE *database = fopen(argv[1], "r");
    if (!database) {
        printf("Error opening database\n");
        return 1;
    }
    if (strcmp(argv[2], "-f") == 0) {
        inp(database, 0);
    } else if (strcmp(argv[2], "-p") == 0) {
        inp(database, 1);
    } else {
        printf("Incorrect flag\n");
    }
    fclose(database);
}
