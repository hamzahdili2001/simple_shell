#include "shell.h"

/**
 * _strchr - function like strchr: read the manual
 * @str: string
 * @c: integer
 * Return: NULL or true
*/

char *_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
	{
		str++;
	}
	return ((*str == (char)c) ? (char *)str : NULL);
}


/**
 * _strdup - function like strdup.
 * @str: String.
 * Return: new String.
*/

char *_strdup(char *str)
{
	char *new_str;
	int len = _strlen(str);

	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	_strcpy(new_str, str);
	return (new_str);
}

/**
 * _strcmp - function like strcmp
 * @s1: string
 * @s2: string
 * Return: s1 - s2
*/

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;
	}

	return (*s1 - *s2);
}

/**
 * _strtok - function like strtok.
 * @str: string
 * @delim: delims
 * Return: Nothing.
*/

char *_strtok(char *str, const char *delim)
{
	static char *pos;
	char *start, *end;

	if (str)
		pos = str;
	if (!pos)
		return (NULL);

	while (*pos && strchr(delim, *pos))
		pos++;

	if (!*pos)
		return (NULL);

	start = pos;
	end = start + strcspn(pos, delim);
	pos = (*end) ? end + 1 : NULL;
	*end = '\0';

	return (start);
}
