#include "shell.h"
#include <stddef.h>

/**
 * _memcpy - copy n bytes from memory area src to dest
 * @dest: pointer to destination memory area
 * @src: pointer to source memory area
 * @n: number of bytes to copy
 * Return: pointer to destination memory area
*/

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	char *dest_c = (char *)dest;
	const char *src_c = (const char *)src;

	for (i = 0; i < n; i++)
	{
		dest_c[i] = src_c[i];
	}
	return (dest);
}


/**
 * _atoi - convert string to integer
 * @str: pointer to string to convert
 * Return: the converted int value
*/

int _atoi(const char *str)
{
	int result = 0;
	int sign = 1;

	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
		{
			break;
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
