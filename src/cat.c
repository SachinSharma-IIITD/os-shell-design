#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int take_input(int nFlag, int eFlag, int lineNo);

int main(int argc, char **argv) {
    int nFlag = 0;
    int eFlag = 0;
    int isFile = 0;
    int lineNo = 1;
    char *data;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-n") == 0) {
            nFlag = 1;
            continue;
        }
        if (strcmp(argv[i], "-E") == 0) {
            eFlag = 1;
            continue;
        }
        isFile = 1;
    }

    // printf("%d\n", nFlag);
    // printf("%d\n", eFlag);
    // printf("%d\n", isFile);

    if (isFile == 0) {
        lineNo = take_input(nFlag, eFlag, lineNo);
        return 0;
    }
    
    FILE *file;

    for (int i = 1; i < argc; i++) {

        if (argv[i][0] == '-') {

            if (strlen(argv[i]) > 1) continue;

            lineNo = take_input(nFlag, eFlag, lineNo);
            continue;
        }

        file = fopen(argv[i], "r");

        if (file == NULL) {
            printf("Unable to open file\n");
            return 1;
        }

        fseek(file, 0L, SEEK_END);
        long size = ftell(file);
        fseek(file, 0L, 0);

        data = (char *)malloc(size);
        
        while (fgets(data, size, file) != NULL) {
            if (nFlag == 1) printf("\t%d. ", lineNo);

            printf("%s", strsep(&data, "\n"));

            if (eFlag == 1) printf("$\n");
            else printf("\n");

            lineNo++;
        }

        fclose(file);
    }

    return 0;
}

int take_input(int nFlag, int eFlag, int lineNo) {
    char *data = (char *)malloc(100);
        
    while (fgets(data, 100, stdin) != NULL) {
        if (nFlag == 1) printf("\t%d. ", lineNo);

        printf("%s", strsep(&data, "\n"));

        if (eFlag == 1) printf("$\n");
        else printf("\n");

        lineNo++;
    }
    return lineNo;
}