#include "main.h"
/**
 * string_printer - prints strings
 * @s: string to be printed
 *
 * Return: number of chars printed in string
 */
int string_printer(char *s)
{
	int i, n = 0;

	if (s != NULL)
	{
		for (i = 0; s[i] != '\0'; i++)
		{
			_putchar(s[i]);
		}
		return (i);
	}
	else
	{
		_putchar('(');
		_putchar('n');
		_putchar('u');
		_putchar('l');
		_putchar('l');
		_putchar(')');
		n = 6;

		return (n);
	}
}


/**
 * _putchar - writes a character to stdout
 * @c: char to print
 *
 * Return: 1 (success), -1 (error)
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * _strdup - duplicates a string
 * @str: string to be duplicated
 *
 * Return: pointer to new string (success), NULL if  string or malloc is NULL
 */
char *_strdup(char *str)
{
	int i = 0, length = 0;
	char *newstr;

	if (str == NULL)
		return (NULL);

	while (str[i] != '\0')
	{
		length++;
		i++;
	}

	newstr = malloc(sizeof(char) * (length + 1));

	for (i = 0; i < str[i]; i++)
		newstr[i] = str[i];
	newstr[i] = '\0';
	return (newstr);
}

/**
 * _strlen - returns length of string
 * @s: string to be measured
 *
 * Return: number of chars, except '\0'
 */
int _strlen(char *s)
{
	int i = 0, length = 0;

	while (s[i] != '\0')
	{
		length++;
		i++;
	}
	return (length);
}

/**
 * _strcpy -  copies a string
 * @src: string to be copied
 * @dest: pointer to destination string
 *
 * Return: value of dest
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';
	return (dest);

}
