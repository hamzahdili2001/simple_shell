#include "shell.h"
#include <stddef.h>

void *_memcpy(void *dest, const void *src, size_t n)
{
    char *dest_c = (char *)dest;
    const char *src_c = (const char *)src;
    for (size_t i = 0; i < n; i++)
    {
        dest_c[i] = src_c[i];
    }
    return (dest);
}

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
