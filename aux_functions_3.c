#include "main.h"

/**
 * _atoi - convert str to int
 * @str: str to convert to int
 * Return: res - num gotten from string
 */
int _atoi(char *str)
{
	int i, res = 0, len = _strlen(str);
	int sign = 1;

	for (i = 0; i < len; i++)
	{
		if (str[i] == '-' && i == 0)
		{
			sign = -1;
			continue;
		}
		res = res * 10 + (str[i] - 48);
	}
	return (res * sign);
}

/**
 * _strncmp - compares s1 and s2 upto n
 * @s1: first string
 * @s2: second string
 * @n: number of characters to compare
 * Return: the difference in comparison
 */

int _strncmp(char *s1, char *s2, int n)
{
	int i = 0, res = 0;

	if (s1 == NULL || s2 == NULL || !n)
		return (-1);

	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] == s2[i])
			res++;
		i++;
	}
	return (n - res);
}
