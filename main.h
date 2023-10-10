#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <dirent.h>

extern char **environ;
volatile int break_loop;

/* struct & typedef */

/**
 * struct bultin - struct for bultin cmd
 * @name: name of cmd
 * @handler: handler for the cmd
 */

typedef struct bultin
{
	char *name;
	void (*handler)(char **, char **);
} bultin;

typedef void (*sighandler_t)(int);

/*AUXILLIARY FUNCTIONS*/
int _putchar(char c);
int string_printer(char *str);
char *_strcpy(char *dest, char *src);
char *_strdup(char *str);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strspn(const char *s, const char *accept);
int _atoi(char *str);
char *_memset(char *s, char b, unsigned int n);
int _strncmp(char *s1, char *s2, int n);

/*MAIN FUNCTIONS*/
void print_prompt(void);
ssize_t line_reader(char **buf, size_t *n);
char **token_generator(char *cmdline, const char *delim, int *ac);
int exec_cmd(char **av, pid_t pid, int *cmdstatus);
char *_getenv(char **envp, char *shortcmd);
int exec_from_path(char **envp, pid_t pid, char **av, int *cmdstatus);
int is_builtin_cmd(char **av, char *cmdline, int status, char ***newenviron,
		char **newentry, int ac);
void exitshell(int status, char **av, char *cmdline,  char **newenviron,
	       char *newentry);
void my_sigint(int signum);
void _printenv(char **av);
void cleanall(char **av, char *cmdline);
void _addenv(char *name, char *value, int envlen, char ***newenviron,
	     char **newentry);
void _updateenv(char **av);
void err_notfound(char *shortcmd);
void clean_cmd(int __attribute__((unused)) ac, char **av);
int exec_cleanup(int exec_return, int ac, char **av);
void _cd(char **av, int ac);
void change_pwd(char *oldpwdpath);
void change_oldpwd(char *pwdpath);
void _handleenv(char **av, char ***newenviron, char **newentry);
int _isvalidenvcmd(char **av);
void get_home(char **homevar);


#endif