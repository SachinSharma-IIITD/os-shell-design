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

int main()
{
    char *binPath = (char *)malloc(100);
    getcwd(binPath, 100);
    strcat(binPath, "/bin/");

    char *input = (char *)malloc(10);
    char *buffer2 = (char *)malloc(3);
    char *buffer4 = (char *)malloc(5);

    while (1)
    {
        prompt();
        fgets(input, 100, stdin);
        input = strcat(strsep(&input, "\n"), "\0");

        buffer2 = strncpy(buffer2, input, 2);
        buffer2 = strcat(buffer2, "\0");
        buffer4 = strncpy(buffer4, input, 4);
        buffer4 = strcat(buffer4, "\0");

        if (strcmp(input, "exit") == 0)
            exit(0);

        else if (strcmp(buffer2, "cd") == 0)
        {
            strsep(&input, " ");
            cd(input);
        }

        else if (strcmp(input, "pwd") == 0)
        {
            pwd();
        }

        else if (strcmp(buffer4, "echo") == 0)
        {
            strsep(&input, " ");
            echo(input);
        }

        else if (strcmp(buffer2, "&t") == 0)
        {
            pthread_t ptid;
            strsep(&input, " ");
            char *command = (char *)malloc(100);
            strcpy(command, binPath);
            strcat(command, input);

            pthread_create(&ptid, NULL, &exec_thread, (void *)command);
            pthread_join(ptid, NULL);
        }

        else
        {
            pid_t pid;
            pid = fork();

            if (pid < 0)
            {
                puts("Fork failed!");
            }
            else if (pid == 0)
            {
                char *command = (char *)malloc(100);
                strcpy(command, binPath);
                char *c_name = strsep(&input, " ");
                strcat(command, c_name);

                char **args = (char **)malloc(100 * sizeof(char *));
                args[0] = c_name;
                int i = 1;

                while (input != NULL)
                {
                    args[i] = strsep(&input, " ");
                    i++;
                }
                args[i] = NULL;

                execv(command, args);
            }
            else
            {
                wait(NULL);
            }
        }
    }
}

void *exec_thread(void *arg)
{
    int status = system((char *)arg);
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