#include "shell.h"

/**
 * _strcat - fonctions line strcat: man strcat
 * @dest: Destination
 * @src: source.
 * Return: Dest
 */

char *_strcat(char *dest, char *src)
{
	int dest_length = _strlen(dest), i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + dest_length) = *(src + i);
		i++;
		dest_length++;
	}
	*(dest + dest_length) = '\0';
	return (dest);
}


/**
 * _strcpy - functions like strcpy: man strcpy
 * @dest: Destination
 * @src: source
 * Return: Destination.
*/
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = *(src + i);
	return (dest);
}

/**
 * _strlen - functions like strlen : man strlen
 * @str: string.
 * Return: Length of str
*/

int _strlen(char *str)
{
	int len = 0;

	while (*(str + len) != '\0')
		len++;

	return (len);
}

/**
 * _isdigit - check if char is digit
 * @c: char
 * Return: 1 or 0
*/

int _isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
