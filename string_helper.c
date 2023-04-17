#include "shell.h"

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

int _strlen(char *str)
{
	int len = 0;

	while (*(str + len) != '\0')
		len++;

	return (len);
}

char *_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
	{
		str++;
	}
        return (*str == (char)c) ? (char*)str : NULL;
}

char *_strdup(char *str)
{
	char *new_str;
	int len = _strlen(str);

	new_str = malloc(sizeof(char) * (len +1));
	if (new_str == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	_strcpy(new_str, str);
	return (new_str);
}

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return *(const unsigned char *)s1 - *(const unsigned char *)s2;
}

char *_strtok(char *str, const char *delim)
{
	static char *p = NULL; // pointer to current position in string
	if (str != NULL) // set pointer to beginning of new string
		p = str;
	if (p == NULL || *p == '\0') // end of string, nothing left to tokenize
		return (NULL);
	char *start = p; // save the starting position
	
	// move pointer to the next delimiter
	while (*p != '\0' && _strchr(delim, *p) == NULL)
		++p;
	if (*p != '\0')
		*p++ = '\0'; // replace the delimiter with nill character
			     // and move the pointer
	return (start); // return the starting position of the next token
}
