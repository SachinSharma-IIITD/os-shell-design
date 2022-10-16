#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <sys/stat.h>

void print_stats(char *fileName, struct stat stats);

int main(int argc, char **argv)
{
    int aFlag = 0;
    int lFlag = 0;
    struct dirent *dirent;
    struct stat stats;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-a") == 0)
            aFlag = 1;
        if (strcmp(argv[i], "-l") == 0)
            lFlag = 1;
    }

    DIR *dir = opendir(".");

    if (dir == NULL)
    {
        puts("Directory couldn't be opened!");
        return 1;
    }

    while ((dirent = readdir(dir)) != NULL)
    {
        if (dirent->d_name[0] == '.')
            continue;

        if (lFlag == 1)
        {
            print_stats(dirent->d_name, stats);
        }
        else
            printf("%s  ", dirent->d_name);
    }

    seekdir(dir, 0L);

    if (aFlag == 1)
    {
        while ((dirent = readdir(dir)) != NULL)
        {
            if (dirent->d_name[0] == '.' && strlen(dirent->d_name) > 2)
            {
                if (lFlag == 1)
                    print_stats(dirent->d_name, stats);
                else
                    printf("%s  ", dirent->d_name);
            }
        }
        if (lFlag == 1)
        {
            print_stats(".", stats);
            print_stats("..", stats);
        }
        else
            printf(".  ..");
    }

    puts("");
    closedir(dir);
    return 0;
}

void print_stats(char *fileName, struct stat stats)
{
    char buffer[40];

    stat((const char *)fileName, &stats);

    strftime(buffer, 40, "%d %B %Y %H:%M:%S IST", localtime((const time_t *)&stats.st_ctim));

    printf("%s ", buffer);
    printf("%6d ", (int)stats.st_size);
    printf("%s\n", fileName);
}