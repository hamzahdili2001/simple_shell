#include "shell.h"

static user_command_t user_commands[5] = {
	{"cd", cd_command},
	{"env", env_command},
	{"echo", echo_command},
	{"setenv", setenv_command},
	{"unsetenv", unsetenv_command},
};

/**
 * find_command - find the commands that the user enter
 * @cmd_name: command name
 * Return: NULL or the the commands if it get found
*/
user_command_t *find_command(char *cmd_name)
{
	int i, num_user_commands = sizeof(user_commands) / sizeof(user_command_t);

	if (cmd_name == NULL)
	{
		return (NULL);
	}

	for (i = 0; i < num_user_commands; i++)
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
	char *bn_command = malloc(_strlen(cmd_name) + _strlen("/bin/"));

	if (bn_command == NULL)
	{
		write(STDERR_FILENO, "Allocation faild\n", _strlen("Allocation faild\n"));
		exit(EXIT_FAILURE);
	}

	_strcpy(bn_command, "/bin/");
	_strcat(bn_command, cmd_name);
	bn_command[_strlen(bn_command)] = '\0';
	return (bn_command);
}

/**
 * execute_external_command - Executes external commands
 * @args: argumments
 * @bin_path: binary path
 * Retrun: Nothing.
*/

void execute_external_command(char **args, char *bin_path)
{
	int status, last_exit_status = 0;
	pid_t pid = fork();

	if (last_exit_status < 0)
		return;

	if (pid == 0)
	{
		if (execve(bin_path, args, NULL) == -1)
		{
			perror("execve");
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
 * Return: Nothing.
*/

void execute_command(char **args)
{
	user_command_t *cmd;
	char *binary_path = NULL;

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
	binary_path = NULL;
}

