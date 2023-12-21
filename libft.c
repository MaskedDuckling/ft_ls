#include "main.h"

int ft_strlen(char *str)
{
    int i = 0;

    while (str[i])
        i++;
    return i;
}

int ft_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return s1[i] - s2[i];
}

char *ft_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i])
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = 0;
    return dest;
}

char *ft_strcat(char *dest, char *src)
{
    int i = 0;
    int j = 0;

    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = 0;
    return dest;
}

char *ft_strjoin(char *s1, char *s2)
{
	char *str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);

	ft_strcpy(str, s1);
	ft_strcat(str, s2);
	return str;
}
