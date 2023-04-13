char *_strcat(char *dest, char *src)
{
	int dest_length = _strlen(dest), i = 0;

	while (*(src + 1) != '\0')
	{
		*(dest + dest_length) = *(src + 1);
		i++;
		dest_length++;
	}
	*(dest + dest_length) = '\0';
	return (dest);
}

char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;

	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	*(dest + i) = *(src + i);
	return (dest);
}

int _strlen(char *s)
{
	int len;

	for (len = 0 ; s[len];)
		len++;
	return (len);
}
