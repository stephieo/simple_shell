#include "main.h"
#include <stdint.h>

/**
 * exec_cmd - Executes the command
 * @av: list of args
 * @pid: proccess id
 * @cmdstatus: exit status pf prev cmd
 * Return: -1 (failed execution), 0 (success)
 */

int exec_cmd(char **av, pid_t pid, int *cmdstatus)
{
	int i = 0, status;

	break_loop = 1;
	pid = fork();
	if (pid == 0)
	{
		while (break_loop)
		{
			signal(SIGINT, my_sigint);
			if (av[i])
			{
				if (execve(av[0], av, NULL) == -1)
				{
					perror("./hsh");
					return (-1);
				}
			}
		}
		for (i = 0; av[i]; i++)
			free(av[i]);
		free(av);
	}
	else if (pid < 0)
	{
		perror("./hsh");
		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			*cmdstatus = WEXITSTATUS(status);
		}
	}
	return (0);
}

/**
 * exec_from_path - creates full path of command and  executes
 * @envp: env variable path
 * @pid: process id
 * @cmdstatus: exit status pf prev cmd
 * @av: user input tokens
 * Return: 1 if error in execution or malloc error,
 * -1 if command doesn't exist
 */

int exec_from_path(char **envp, pid_t pid, char **av, int *cmdstatus)
{
	char *shortcmd = av[0], *fullpath = NULL;
	int status;

	break_loop = 1;
	fullpath = _getenv(envp, shortcmd);
	if (fullpath == NULL)
	{
		clean_cmd(1, av);
		return (127);
	}
	pid = fork();
	if (pid == 0)
	{
		while (break_loop)
		{
			signal(SIGINT, my_sigint);
			if (execve(fullpath, av, NULL) == -1)
			{
				free(fullpath);
				perror("./hsh");
				return (-1);
			}
		}
		free(fullpath);
	}
	else if (pid < 0)
	{
		perror("./hsh");
		exit(1);
	}
	else
	{
		wait(&status);
		if (WIFEXITED(status))
		{
			*cmdstatus = WEXITSTATUS(status);
		}
		free(fullpath);
	}
	return (0);
}

/**
 * _getenv - gets the desired environment variabl
 * @envp: environment array
 * @shortcmd: command to turn to full path
 *
 * Return: full path otf command
 */

char *_getenv(char **envp, char *shortcmd)
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

/**
 * is_bultin_cmd - checks whether command is a built in
 * @av: tokens from terminal
 * @cmdline: shell cmdline
 * @status: status of exit of prev cmd
 * @newenviron: ptr to env copy
 * @newentry: ptr to new entry in environ
 * Return: cmd handler
 */

int is_builtin_cmd(char **av, char *cmdline, int status, char ***newenviron,
		char **newentry, int ac)
{
	char *cmd = av[0];

	if (_strcmp("exit", cmd) == 0)
	{
		exitshell(status, av, cmdline, (*newenviron), (*newentry));
		return (0);
	}
	if (_strcmp("env", cmd) == 0)
	{
		_printenv(av);
		return (0);
	}
	if (_strcmp("setenv", cmd) == 0 || _strcmp("unsetenv", cmd) == 0)
	{
		_handleenv(av, newenviron, newentry);
		return (0);
	}
	if (_strcmp("cd", cmd) == 0)
	{
		_cd(av, ac);
		return (0);
	}
	return (-1);
}

/**
 * exitshell - handler for exit cmd in shell
 * @av: user input lis
 * @status: status of exit pf prev cmd
 * @cmdline: cmdline fof shell
 * @newenviron: env copy
 * @newentry: new entry in env
 * Return: void
 */

void exitshell(int status, char **av, char *cmdline,
	       char **newenviron, char *newentry)
{
	int et;
	uintptr_t intstat;

	if (av[1])
	{
		et = _atoi(av[1]);
		if (et < 0)
		{
			perror("./hsh");
			exit(2);
		}
		else if (et > 0)
		{
			cleanall(av, cmdline);
			if (newenviron != NULL)
				free(newenviron);
			if (newentry != NULL)
				free(newentry);
			exit(et);
		}
		intstat = (uintptr_t)av[0];
		exit(intstat);
	}
	cleanall(av, cmdline);
	if (newenviron != NULL)
		free(newenviron);
	if (newentry != NULL)
		free(newentry);
	exit(status);
}
