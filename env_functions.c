#include "main.h"

/**
 * _handle_set_unset - sets env variable to a new val
 * @av: user input toks
 * @newenviron: environ temp ptr
 * @newentry: new env ptr
 */

void _handle_set_unset(char **av, char ***newenviron, char **newentry)
{
	char *ev = NULL, *name, *value;
	int i, namelen, id = -1, envlen, hasvalidargs = _isvalidenvcmd(av);

	if (!hasvalidargs)
		return;
	name = av[1], value = av[2];
	namelen = _strlen(name);
	for (i = 0; environ[i]; i++)
		if (_strncmp(environ[i], name, namelen) == 0 &&
			(environ[i][namelen] == '=') && id == -1)
		{
			ev = environ[i];
			id = i;
		}
	envlen = i;
	if (value == NULL || (_strcmp(av[0], "unsetenv") == 0))
	{
		if (id > -1)
			environ[id] = "";
		cleanall(av, NULL);
		return;
	}
	if (ev == NULL && id == -1)
	{
		_addenv(name, value, envlen, newenviron, newentry);
		cleanall(av, NULL);
		return;
	}
	*newentry = malloc(_strlen(value) + namelen + 2);
	if (*newentry == NULL)
	{
		perror("Malloc");
		return;
	}
	_strcpy(*newentry, name);
	_strcat(*newentry, "=");
	_strcat(*newentry, value);
	environ[id] = *newentry;
	cleanall(av, NULL);
}


/**
 * _addenv - add env to environ
 * @name: name of env
 * @value: value of env
 * @newenviron: ptr to env copy
 * @envlen: size of environ
 * @newentry: ptr to new entry
 */

void _addenv(char *name, char *value, int envlen,
	     char ***newenviron, char **newentry)
{
	int i, len;

	*newenviron = malloc((envlen + 2) * sizeof(char *));
	if (*newenviron == NULL)
	{
		perror("Malloc");
		return;
	}
	len = _strlen(value) + _strlen(name) + 2;
	*newentry = malloc(len);

	if (*newentry == NULL)
	{
		perror("Malloc");
		free(*newenviron);
		return;
	}
	_strcpy(*newentry, name);
	_strcat(*newentry, "=");
	_strcat(*newentry, value);
	for (i = 0; environ[i] != NULL; i++)
		(*newenviron)[i] = environ[i];
	(*newenviron)[i] = *newentry;
	(*newenviron)[++i] = NULL;
	environ = *newenviron;
}

/**
 * _isvalidenvcmd - if handles printenv and cleans up after
 * @av: user toks
 * Return: 1 if it has the right arg count or 0 if not
 */

int _isvalidenvcmd(char **av)
{
	int i = 0;

	while (av[i] != NULL)
		i++;

	if (i < 2 || (_strcmp(av[0], "setenv") == 0 && i < 3))
	{
		cleanall(av, NULL);
		return (0);
	}
	return (1);
}





/**
 *_printenv - prints environment variable
 *@av: input list
 */

void _printenv(char **av)
{
	int i;

	cleanall(av, NULL);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strlen(environ[i]))
		{
			write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
			_putchar('\n');
		}
	}
}

/**
 * _getfullpath - gets the desired environment variabl
 * @envp: environment array
 * @shortcmd: command to turn to full path
 *
 * Return: full path otf command
 */

char *_getfullpath(char **envp, char *shortcmd)
{
	int i = 0;
	char *currentvar, *Eval = NULL, *dir, *fullpath = NULL, temp[1024];
	struct stat filecheck;

	while (envp[i])
	{
		_strcpy(temp, envp[i]);
		currentvar = strtok(temp, "=");
		if (!(_strcmp(currentvar, "PATH")))
			break;
		i++;
	}
	Eval = strtok(NULL, "=");
	dir = strtok(Eval, ":");
	while (dir)
	{
		fullpath = malloc(_strlen(dir) + _strlen(shortcmd) +  2);
		if (fullpath == NULL)
		{
			perror("Memory allocation error");
			free(fullpath);
			return (NULL);
		}
		_memset(fullpath, 0, _strlen(dir) + _strlen(shortcmd) +  2);
		fullpath[0] = '0';
		_strcpy(fullpath, dir);
		_strcat(fullpath, "/");
		_strcat(fullpath, shortcmd);
		if ((stat(fullpath, &filecheck)) == 0)
			return (fullpath);
		free(fullpath);
		dir = strtok(NULL, ":");
		if (dir)
			continue;
		break;
	}
	err_notfound(shortcmd);
	return (NULL);
}
