#include "shell.h"
#include <stdio.h>

static user_command_t user_commands[6] = {
	{"cd", cd_command},
	{"env", env_command},
	{"echo", echo_command},
	{"setenv", setenv_command},
	{"unsetenv", unsetenv_command},
	{"exit", exit_command},
};

/**
 * find_command - find the commands that the user enter
 * @cmd_name: command name
 * Return: NULL or the the commands if it get found
*/
user_command_t *find_command(char *cmd_name)
{
	int i, num_user_commands = sizeof(user_commands) / sizeof(user_command_t);

	(void)num_user_commands;
	if (cmd_name == NULL)
	{
		return (NULL);
	}

	for (i = 0; user_commands[i].command_name; i++)
	{
		if (_strcmp(cmd_name, user_commands[i].command_name) == 0)
			return (&user_commands[i]);
	}
	return (NULL);
}


/**
 * build_bin_path - Builds the full path to the binary
 * @cmd_name: command name
 * Return: the command
*/
char *build_bin_path(char *cmd_name)
{
	char *path = getenv("PATH"), *path_copy = strdup(path),
	*path_dir = _strtok(path_copy, ":"),
	*bn_command = malloc(sizeof(char *) * BUFFER_SIZE);

	if (path == NULL)
	{
		perror("Error: PATH environment variable not set");
		return (NULL);
	}
	if (path_copy == NULL)
	{
		perror("Error: strdup failed");
		return (NULL);
	}

	if (bn_command == NULL)
	{
		perror("Error: malloc failed");
		free(path_copy);
		return (NULL);
	}

	while (path_dir != NULL)
	{
		_strcpy(bn_command, path_dir);
		_strcat(bn_command, "/");
		_strcat(bn_command, cmd_name);
		if (access(bn_command, X_OK) == 0)
		{
			free(path_copy);
			return (bn_command);
		}
		path_dir = _strtok(NULL, ":");
	}
	free(path_copy);
	return (bn_command);
}

/**
 * execute_external_command - Executes external commands
 * @args: argumments
 * @bin_path: binary path
 * @argv: argumments form the main
 * Retrun: Nothing.
*/

void execute_external_command(char **args, char *bin_path, char *argv[])
{
	int status, last_exit_status = 0;
	pid_t pid = fork();

	if (last_exit_status < 0)
		return;

	if (pid == 0)
	{
		if (execve(bin_path, args, environ) == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		}  while (!WIFEXITED(status) && !WIFSIGNALED(status));
		 last_exit_status = WEXITSTATUS(status);
	}
}
/**
 * execute_user_command - Executes normal user commands
 * @cmd: command
 * @args: argumments.
 * Return: Nothing.
*/
void execute_user_command(user_command_t *cmd, char **args)
{
	cmd->command_function(args);
}

/**
 * execute_command - Executes all the commands that the user enters
 * @args: argumments
 * @argv: argumments from the main
 * Return: Nothing.
*/

void execute_command(char **args, char *argv[])
{
	user_command_t *cmd;
	char *binary_path = NULL;

	if (args[0] == NULL)
		return;

	if (args[0][0] == '/')
	{
		execute_external_command(args, args[0], argv);
		return;
	}

	cmd = find_command(args[0]);

	if (cmd != NULL)
	{
		execute_user_command(cmd, args);
		return;
	}

	binary_path = build_bin_path(args[0]);

	execute_external_command(args, binary_path, argv);

	free(binary_path);
	binary_path = NULL;
}

