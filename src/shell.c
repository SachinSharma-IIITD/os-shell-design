#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <string.h>

void *exec_thread(void *arg);
void cd(char *path);
void echo(char *input);
void pwd();
void prompt();
void clear();

int main()
{
    char *binPath = (char *)malloc(100);
    getcwd(binPath, 100);
    strcat(binPath, "/bin/");

    char *input = (char *)malloc(100);
    char *inputArgs = (char *)malloc(100);

    while (1)
    {
        prompt();
        scanf("%s", input);

        // puts(input);

        if (strcmp(input, "exit") == 0)
            exit(0);

        else if (strcmp(input, "cd") == 0)
        {
            fgets(inputArgs, 100, stdin);
            inputArgs = strsep(&inputArgs, "\n");

            if (inputArgs[0] == ' ')
            {
                strsep(&inputArgs, " ");
            }
            if (inputArgs[0] == '\0')
                pwd();
            else
                cd(inputArgs);

            continue;
        }

        else if (strcmp(input, "pwd") == 0)
        {
            pwd();
            continue;
        }

        else if (strcmp(input, "echo") == 0)
        {
            fgets(inputArgs, 100, stdin);
            inputArgs = strsep(&inputArgs, "\n");

            if (inputArgs[0] == ' ')
            {
                strsep(&inputArgs, " ");
            }

            if (inputArgs[0] == '\0')
                continue;
            echo(inputArgs);
            continue;
        }

        else if (strcmp(input, "clear") == 0)
        {
            clear();
            continue;
        }

        else if (strcmp(input, "&t") == 0)
        {
            pthread_t ptid;

            fgets(inputArgs, 100, stdin);
            inputArgs = strsep(&inputArgs, "\n");

            if (inputArgs[0] == ' ')
            {
                strsep(&inputArgs, " ");
            }

            char *command = (char *)malloc(100);
            strcpy(command, binPath);
            strcat(command, inputArgs);

            pthread_create(&ptid, NULL, &exec_thread, (void *)command);
            pthread_join(ptid, NULL);
            continue;
        }

        else
        {
            // puts("process...");
            pid_t pid;
            pid = fork();

            if (pid < 0)
            {
                puts("Fork failed!");
                return -1;
            }
            else if (pid == 0)
            {
                char *command = (char *)malloc(100);
                strcpy(command, binPath);
                // char *c_name = input;
                strcat(command, input);

                fgets(inputArgs, 100, stdin);
                inputArgs = strsep(&inputArgs, "\n");
                // puts(inputArgs);

                if (inputArgs[0] == ' ')
                {
                    strsep(&inputArgs, " ");
                }

                char **args = (char **)malloc(100 * sizeof(char *));
                args[0] = input;
                int i = 1;

                if (inputArgs[0] != '\0')
                {
                    while (inputArgs != NULL)
                    {
                        args[i] = strsep(&inputArgs, " ");
                        i++;
                    }
                }
                args[i] = NULL;

                execv(command, args);
                return 0;
            }
            else
            {
                wait(NULL);
                // puts("...completed");
                fgets(input, 100, stdin);
                continue;
            }
        }
    }
}

void *exec_thread(void *arg)
{
    system((char *)arg);
    pthread_exit(NULL);
}

void prompt()
{
    char *cwd = (char *)malloc(100);
    getcwd(cwd, 100);
    char *hostname = (char *)malloc(20);
    gethostname(hostname, 20);
    printf("\n[%s@%s]:%s > ", getenv("USER"), hostname, cwd);
    free(cwd);
    free(hostname);
    return;
}

void cd(char *path)
{
    int status = chdir(path);

    if (status != 0)
    {
        printf("Cannot change to '%s'", path);
        return;
    }
    return;
}

void echo(char *input)
{
    puts(input);
    return;
}

void pwd()
{
    char *buffer = (char *)malloc(100);
    getcwd(buffer, 100);
    puts(buffer);
    return;
}

void clear()
{
    printf("\e[1;1H\e[2J");
}