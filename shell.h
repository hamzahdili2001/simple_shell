#ifndef SHELL_H
#define SHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <ncurses.h>
#define TOKEN_DELIM " \t\r\n\a"
#define BUFFER_SIZE 1024

/*EXTERNAL VAR*/
extern int last_exit_status;
extern char **environ;

/*MAIN FUNCTIONS*/
void main_loop(void);
char *read_line(void);
void execute_command(char **args);
char **parse_line(char *line);
void env_command(char **args);

/*EXTERNAL COMMANDS FUNCTIONS*/
void cd_command(char **args);
void setenv_command(char **args);
void unsetenv_command(char **args);
void echo_command(char **args);
void exit_command(char **args);
/*STRING FUNCTIONS*/
int _strlen(char *str);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, char *src);
char *_strcpy(char *dest, char *src);
void clear_command(char **args);
char *_strtok(char *str, const char *delim);
char *_strchr(const char *str, int c);

/*OWN FUNCTION*/
void *_memcpy(void *dest, const void *src, size_t n);
int _atoi(const char *str);
int _isdigit(int c);
/*ERRORS FUCNTION*/
void errors(char *name);
/**
 * struct user_command_t - struct that call function based on command
 * @command_name: command name
 * @command_function: function ointer that get called when
 *								the user enter command
*/
typedef struct user_command_t
{
	char *command_name;
	void (*command_function)(char **args);
} user_command_t;
#endif
