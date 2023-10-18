#include  "main.h"

/**
 * main- entry point
 * @argc: number of arguments
 * @argv: array of arguments
 * @env: array of env variables
 *
 * Return: 1( success)
 */

int main(int __attribute__((unused)) argc,
	 __attribute__((unused)) char **argv,
	__attribute__((unused)) char **env
	)
{
	pid_t pid = 0;
	ssize_t gt_status;
	char *cmdline = NULL, *newentry = NULL;
	size_t n = 50;
	const char *delim = " \t\f\r\n";
	int ac = 0, cmdstatus = 0, exec_return, trigger;
	char **av = NULL, **newenviron = NULL;

	break_loop = 1;
	while (break_loop)
	{
		print_prompt();
		signal(SIGINT, my_sigint);
		gt_status = line_reader(&cmdline, &n);
		if (gt_status == 1)
			continue;
		else if (gt_status == -1)
			exit(0);
		av = token_generator(cmdline, delim, &ac);
		if ((is_builtin_cmd(av, cmdline, cmdstatus, &newenviron,
				 &newentry, ac)) == 0)
			continue;
		else if (access(av[0], F_OK) != 0)
		{
			exec_return = exec_from_path(env, pid, av, &cmdstatus);
			trigger = exec_cleanup(exec_return, ac, av);
			if (trigger == 127)
				break;
			else if (trigger == -1)
				continue;
		}
		else if ((access(av[0], F_OK) == 0))
		{
			if ((spawn_and_exec_cmd(av, pid, &cmdstatus)) == -1)
				continue;
		}
	clean_cmd(ac, av);
	}
	free(cmdline);
	return (trigger == 127 ? 127 : 0);
}
