#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>

int main(int argc, char **argv)
{
    int mFlag;
    int vFlag;
    int isReadable = 0;
    int isWritable = 0;
    int isExec = 0;

    if (argc <= 1)
    {
        printf("Missing arguments!\n");
        return 1;
    }

    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-m") == 0)
            mFlag = 1;
        if (strcmp(argv[i], "-v") == 0)
            vFlag = 1;

        if (mFlag == 1)
        {
            if (argv[i][0] == '+')
            {
                for (int j = 1; j < strlen(argv[i]); j++)
                {
                    if (argv[i][j] == 'r')
                        isReadable = 1;
                    if (argv[i][j] == 'w')
                        isWritable = 1;
                    if (argv[i][j] == 'x')
                        isExec = 1;
                }
            }
        }
    }

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-' || argv[i][0] == '+')
            continue;

        // RW
        if (isReadable == 1 && isWritable == 1 && isExec == 0)
        {
            int status = mkdir(argv[i], S_IWRITE | S_IREAD);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // RX
        if (isReadable == 1 && isWritable == 0 && isExec == 1)
        {
            int status = mkdir(argv[i], S_IREAD | S_IEXEC);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // WX
        if (isReadable == 0 && isWritable == 1 && isExec == 1)
        {
            int status = mkdir(argv[i], S_IWRITE | S_IEXEC);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // R
        if (isReadable == 1 && isWritable == 0 && isExec == 0)
        {
            int status = mkdir(argv[i], S_IREAD);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // W
        if (isReadable == 0 && isWritable == 1 && isExec == 0)
        {
            int status = mkdir(argv[i], S_IWRITE);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // X
        if (isReadable == 0 && isWritable == 0 && isExec == 1)
        {
            int status = mkdir(argv[i], S_IEXEC);
            if (status != 0)
                printf("%s\n", strerror(errno));

            else if (vFlag == 1)
                printf("mkdir: created directory '%s'\n", argv[i]);
            continue;
        }
        // RWX
        int status = mkdir(argv[i], S_IRWXU);
        if (status != 0)
            printf("%s\n", strerror(errno));

        else if (vFlag == 1)
            printf("mkdir: created directory '%s'\n", argv[i]);
        continue;
    }
}