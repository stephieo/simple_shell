#include "main.h"

/**
 * print_prompt - Print the shell prompt
 */

void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDIN_FILENO, "$ ", 2);
}

/**
 * line_reader - Reads the command line
 * @buf: Pointer to hold the command line
 * @n: size of the buffer
 * Return: the number of characters read in the line,
 * -1(getline error), 1( blank spaces)
*/


ssize_t line_reader(char **buf, size_t *n)
{
	ssize_t shellstate = getline(buf, n, stdin);

	if (shellstate == -1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(*buf);
		return (-1);
	}
	if (_strspn(*buf, " \t\n\f\r") == _strlen(*buf))
	{
		return (1);
	}

	return (shellstate);
}
/**
 * token_generator - Tokenize the cmdline into a list of strings
 * @cmdline: the cmdline to tokenize
 * @delim: Delimiter string
 * @ac: pointer to hold the number of tokens
 * Return: list of tokens
 */

char **token_generator(char *cmdline, const char *delim, int *ac)
{
	char *buf1 = _strdup(cmdline), *buf2 = _strdup(cmdline), *newtok, **av = NULL;
	int i, toklen;

	*ac = 0;
	newtok = strtok(buf1, delim);
	while (newtok)
	{
		newtok = strtok(NULL, delim);
		(*ac)++;
	}
	av = malloc(sizeof(char *) * ((*ac) + 1));
	if (!av)
	{
		perror("Memory allocation error");
		free(buf2);
		return (NULL);
	}
	for (i = 0; i < *ac; i++)
		av[i] = NULL;
	newtok = strtok(buf2, delim);
	i = 0;
	while (newtok)
	{
		toklen = _strlen(newtok);
		av[i] = malloc(sizeof(char) * (toklen + 1));
		if (av[i] == NULL)
		{
			perror("Memory allocation error");
			for (i = 0; i < (*ac); i++)
				free(av[i]);
			exit(1);
		}
		_strcpy(av[i], newtok);
		newtok = strtok(NULL, delim);
		i++;
	}
	av[*ac] = NULL;
	free(buf1);
	free(buf2);
	return (av);
}

