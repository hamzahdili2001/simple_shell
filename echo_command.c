#include "shell.h"
#include <unistd.h>
#include <string.h>


void echo_command(char **args)
{
    int i, no_newline = 0;
    char *arg, *var_name, *var_value;
    char newline = '\n';
    int stdout_fd = 1; // stdout file descriptor
		int last_exit_status = 0;

    if (args[1] != NULL && _strcmp(args[1], "-n") == 0)
    {
        no_newline = 1;
        args++;
    }

    for (i = 1; args[i] != NULL; i++)
    {
        arg = args[i];

        if (_strcmp(arg, "$?") == 0)
        {
            int exit_status = last_exit_status;
            char exit_status_str[16];
            int exit_status_len = 0;
            if (exit_status == 0) {
                exit_status_str[exit_status_len++] = '0';
            } else {
                while (exit_status != 0) {
                    exit_status_str[exit_status_len++] = '0' + (exit_status % 10);
                    exit_status /= 10;
                }
            }
            for (int j = 0; j < exit_status_len / 2; j++) {
                char tmp = exit_status_str[j];
                exit_status_str[j] = exit_status_str[exit_status_len - j - 1];
                exit_status_str[exit_status_len - j - 1] = tmp;
            }
            write(stdout_fd, exit_status_str, exit_status_len);
        }
        else if (_strcmp(arg, "$$") == 0)
        {
            int pid = getpid();
            char pid_str[16];
            int pid_len = 0;
            if (pid == 0) {
                pid_str[pid_len++] = '0';
            } else {
                while (pid != 0) {
                    pid_str[pid_len++] = '0' + (pid % 10);
                    pid /= 10;
                }
            }
            for (int j = 0; j < pid_len / 2; j++) {
                char tmp = pid_str[j];
                pid_str[j] = pid_str[pid_len - j - 1];
                pid_str[pid_len - j - 1] = tmp;
            }
            write(stdout_fd, pid_str, pid_len);
        }
        else if (arg[0] == '$')
        {
            var_name = arg + 1;
            var_value = getenv(var_name);
            if (var_value != NULL)
            {
                size_t var_value_len = strlen(var_value);
                write(stdout_fd, var_value, var_value_len);
            }
        }
        else
        {
            size_t arg_len = strlen(arg);
            write(stdout_fd, arg, arg_len);
        }

        if (args[i + 1] != NULL)
        {
            write(stdout_fd, " ", 1);
        }
    }

    if (!no_newline)
    {
        write(stdout_fd, &newline, 1);
    }
}

