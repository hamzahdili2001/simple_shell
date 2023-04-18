#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int last_exit_status = 0;

user_command_t user_commands[] = 
{
	{"cd", cd_command},
	{"env", env_command},
	{"exit", exit_command},
	{"echo", echo_command},
	{"setenv", setenv_command},
	{"unsetenv", unsetenv_command},
};

user_command_t *find_command(char *cmd_name)
{
	int i;

	for (i = 0; i < NUM_USER_COMMANDS; i++)
	{
		if (_strcmp(cmd_name, user_commands[i].command_name) == 0)
			return (&user_commands[i]);
	}
	return (NULL);
}

char *build_bin_path(char *cmd_name)
{
	char *bn_command = malloc(_strlen(cmd_name) + _strlen("/bin/"));
	
	if (bn_command == NULL)
	{
		write(STDERR_FILENO, "Allocation faild\n", _strlen("Allocation faild\n"));
		exit(EXIT_FAILURE);
	}

	_strcpy(bn_command, "/bin/");
	_strcat(bn_command, cmd_name);

	return (bn_command);
}

void execute_external_command(char **args, char *bin_path)
{
	int status;
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execve(bin_path, args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0) {
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else {
		do {
			waitpid(pid, &status, WUNTRACED);
		}  while (!WIFEXITED(status) && !WIFSIGNALED(status));
		 last_exit_status = WEXITSTATUS(status);
	}
}

void execute_user_command(user_command_t *cmd, char **args)
{
	cmd->command_function(args);
}

void execute_command(char **args)
{
	user_command_t *cmd;
	char *binary_path;

	if (args[0] == NULL)
		return;
		
	cmd = find_command(args[0]);

	if (cmd != NULL)
	{
		execute_user_command(cmd, args);
		return;
	}

	if (args[0][0] == '/')
	{
		execute_external_command(args, args[0]);
		return; 
	}

	binary_path = build_bin_path(args[0]);

	execute_external_command(args, binary_path);
	
	free(binary_path);
}

