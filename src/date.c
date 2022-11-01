#define _XOPEN_SOURCE 700
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<sys/stat.h>

int main(int argc, char **argv) {
    int dFlag = 0;
    int rFlag = 0;
    struct tm tm;
    char strDate[40];

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0) dFlag = 1;
        if (strcmp(argv[i], "-r") == 0) rFlag = 1;
        if (argv[i][0] == '-' && strcmp(argv[i], "-i") != 0 && strcmp(argv[i], "-v") != 0) {
            puts("Illegal option!");
            return 1;
        }
    }

    if (dFlag == 1 && rFlag == 1) {
        printf("date: -d and -r must be mutually exclusive!\n");
        return 1;
    }

    if (dFlag == 0 && rFlag == 0) {
        if (argc == 1) {
            time_t now;
            time(&now);
            tm = *localtime((const time_t *) &now);
            strftime(strDate, 40, "%A, %d %B %Y %H:%M:%S IST", &tm);
            puts(strDate);
            return 0;
        }
        else {
            printf("Invalid arguments!\n");
            return 1;
        }
    }

    if (dFlag == 1) {
        if (argc < 2) {
            printf("Date string not specified!\n");
            return 1;
        }

        strptime(argv[2], "%d-%m-%Y", &tm);
        strftime(strDate, 40, "%A, %d %B %Y", &tm);
        puts(strDate);
        return 0;
    }

    if (rFlag == 1) {
        if (argc < 2) {
            printf("Date string not specified!\n");
            return 1;
        }

        struct stat stats;
        int status = stat(argv[2], &stats);

        if (status != 0) {
            printf("Couldn't get the modified time for '%s'\n", argv[2]);
            return 1;
        }

        strftime(strDate, 40, "%A, %d %B %Y %H:%M:%S IST", localtime((const time_t *)&stats.st_ctim));
        puts(strDate);
        return 0;
    }

    return 0;
}