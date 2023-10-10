#include "main.h"

/**
 * my_sigint - cleans up shell on SIGINT signal
 * @signum: Signal number
 */

void my_sigint(int signum)
{
	(void)signum;
	/*write(STDOUT_FILENO, "sigint", 6);*/
	break_loop = 0;
}



