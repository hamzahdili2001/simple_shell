#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define PROMPT "#cisfun$ "

/**
 * main - Simple Unix Shell
 *
 * Return: Always 0.
 */
int main(void)
{
        char *line = NULL;
        size_t bufsize = 0;
        ssize_t linelen;
        int status;
        pid_t pid;
        char **environ = NULL;

        while (1) {
		char *args[2] = {NULL, NULL};

                write(STDOUT_FILENO, PROMPT, sizeof(PROMPT));
                linelen = getline(&line, &bufsize, stdin);
                if (linelen == -1) {
                        break;
                } else if (linelen > 1) {
                        line[linelen-1] = '\0';
                        pid = fork();

                        if (pid < 0) {
                                perror("fork");
                                exit(EXIT_FAILURE);
                        }

                        if (pid == 0) {
                                
                                args[0] = line;

                                if (execve(args[0], args, environ) == -1) {
                                        perror("execve");
                                        exit(EXIT_FAILURE);
                                }
                        }

                        
                        if (waitpid(pid, &status, 0) == -1) {
                                perror("waitpid");
                                exit(EXIT_FAILURE);
                        }
                }
        }

        free(line);
        return 0;
}

