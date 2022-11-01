#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

void print_stats(char *dirPath, char *fileName, struct stat stats);

int main(int argc, char **argv)
{
    int aFlag = 0;
    int lFlag = 0;
    char *dirPath = ".";
    struct dirent *dirent;
    struct stat stats;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0)
        {
            aFlag = 1;
            continue;
        }
        if (strcmp(argv[i], "-l") == 0)
        {
            lFlag = 1;
            continue;
        }
        if (argv[i][0] == '-' && strcmp(argv[i], "-a") != 0 && strcmp(argv[i], "-l") != 0) {
            puts("Illegal option!");
            return 1;
        }
        dirPath = argv[i];
    }

    DIR *dir = opendir(dirPath);

    if (dir == NULL)
    {
        printf("[%s]: Directory couldn't be opened!\n", dirPath);
        return 1;
    }

    while ((dirent = readdir(dir)) != NULL)
    {
        if (dirent->d_name[0] == '.')
            continue;

        if (lFlag == 1)
            print_stats(dirPath, dirent->d_name, stats);

        else
            printf("%s  ", dirent->d_name);
    }

    seekdir(dir, 0L);

    if (aFlag == 1)
    {
        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] == '.' && strcmp(dirent->d_name, "..") != 0 && strlen(dirent->d_name) > 1) // for archived folders
            {
                if (lFlag == 1)
                    print_stats(dirPath, dirent->d_name, stats);

                else
                    printf("%s  ", dirent->d_name);
            }
        }
        if (lFlag == 1)
        {
            print_stats(dirPath, ".", stats);
            print_stats(dirPath, "..", stats);
        }
        else
            printf(".  ..");
    }

    puts("");
    closedir(dir);
    return 0;
}

void print_stats(char *dirPath, char *fileName, struct stat stats)
{
    char buffer[40];
    char *filePath = (char *)malloc(1000);
    strcpy(filePath, dirPath);
    strcat(filePath, "/");
    strcat(filePath, fileName);

    stat((const char *)filePath, &stats);

    strftime(buffer, 40, "%d %B %Y %H:%M:%S IST", localtime((const time_t *)&stats.st_ctim));

    printf("%s ", buffer);
    printf("%6d ", (int)stats.st_size);
    printf("%s\n", fileName);
    free(filePath);
}