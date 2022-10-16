#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char **argv) {
    int iFlag = 0;
    int vFlag = 0;

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0) iFlag = 1;
        if (strcmp(argv[i], "-v") == 0) vFlag = 1;
    }
    
    if (argc <= 1) {
        printf("Missing argument!\n");
        return 1;
    }

    FILE *file;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') continue;

        if (iFlag == 1) {
            file = fopen(argv[i], "r");

            if (file == NULL) {
                printf("[%s]: File doesn't exist!\n", argv[i]);
                continue;
            }
            fclose(file);

            printf("rm: remove '%s'? -> ", argv[i]);
            char input[3];
            scanf("%s", input);

            if (input[0] != 'y') {
                if (vFlag == 1) {
                    printf("Deleting '%s' cancelled\n", argv[i]);
                }
                continue;
            }
        }

        int status = remove(argv[i]);

        if (status != 0) printf("[%s]: File doesn't exist!\n", argv[i]);
        else {
            if (vFlag == 1) printf("[%s]: File deleted successfully\n", argv[i]);
            else continue;
        } 
    }

    return 0;
}
