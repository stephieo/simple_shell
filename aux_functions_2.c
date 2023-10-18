#include "main.h"

/**
 * _strcmp - comparing two strings
 * @s1: first string
 * @s2: secon string
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0 if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	int i, ret_val;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] == s2[i])
			ret_val = 0;
		else if (s1[i] < s2[i])
			return (ret_val = (s1[i] - s2[i]));
		else if (s1[i] > s2[i])
			return (ret_val = (s1[i] - s2[i]));
	}
	return (ret_val);
}

/**
 * _strcat - concatenates source to destination string
 * @dest: destination string
 * @src: source string
 * Return: pointer to destination string
 */
char *_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;

	for (j = 0; src[j]; )
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest);
}


/**
 * _strspn - gets length of prefix substring
 * @s: string to check
 * @accept: set of required chars
 *
 * Return: number of initial chars that are in accept
 */

int _strspn(const char *s, const char *accept)
{
	int i, j;
	unsigned int k = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				k++;
				break;
			}
		}
	}
	return (k);

}


/**
 * _memset - fills memory with a constant byte
 * @s: beginning of memory area
 * @b: byte to fill memory with
 * @n: number of bytes to be filled
 *
 * Return: address of memoy area filled
 */

char *_memset(char *s, char b, unsigned int n)
{

	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}
