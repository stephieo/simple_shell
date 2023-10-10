#include "main.h"

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

/**
 * clean_cmd - cleans up av and its elements
 * @ac: argument count
 * @av: argument vector
 */

void clean_cmd(int __attribute__((unused)) ac, char **av)
{
	int i;

	for (i = 0; i < ac || av[i] != NULL; i++)
		free(av[i]);
	free(av);
}

/**
 * cleanall - clean args and cmdline
 * @av: user input tokens
 * @cmdline: cmdline for shell
 */

void cleanall(char **av, char *cmdline)
{
	int i;

	for (i = 0; av[i] != NULL; i++)
	{
		free(av[i]);
	}
	free(av);
	if (cmdline != NULL)
		free(cmdline);

}

/**
 * err_notfound - error printer for nonexistent commands
 * @shortcmd: nonexistent command
 */
void err_notfound(char *shortcmd)
{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, shortcmd, _strlen(shortcmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
 * exec_cleanup - cleans up based on return value
 * @exec_return: return value of exec_fullcmd
 * @ac: argument count
 * @av: argument vector
 *
 * Return: trigger to continue ( ) or break ( )
 */
int exec_cleanup(int exec_return, int ac, char **av)
{
	if (exec_return == 127)
	{
		return (127);
	}
	else if (exec_return == -1)
	{
		clean_cmd(ac, av);
		return (-1);
	}
	return (0);
}
