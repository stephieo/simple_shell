#include "main.h"

/**
 * _cd - changes directory & udates PWD and OLDPWD
 * @av: argument vector
 *
 */
void _cd(char __attribute__((unused))**av, int ac)
{
	char *buffer = malloc(1024), *oldcwd = NULL,
	     *cwd = malloc(1024), *homevar, *temp;

	getcwd(buffer, 1024);
	_strcpy(cwd, buffer);
	printf("cwd is: %s\n", cwd);
	if (av[ac - 1] != av[0])
	{
		if (chdir(av[1]) != -1)
		{
			oldcwd = malloc(1024);
			_strcpy(oldcwd, cwd);
			getcwd(buffer, 1024);
			_strcpy(cwd, buffer);
			change_pwd(cwd);
			change_oldpwd(oldcwd);
			free(buffer);
			free(oldcwd);
			free(cwd);
			clean_cmd(1, av);
		}
		else
		{
			perror("failed: ");
			free(buffer);
			free(cwd);
			clean_cmd(1, av);
		}
	}
	else
	{
		get_home(&homevar);
		/*printf("%s\n",homevar);*/
		oldcwd = malloc(1024);
		/*_strcpy(oldcwd, cwd);
		printf("oldcwd %s\n",oldcwd);*/
		temp = cwd;
		oldcwd = temp;
		printf("oldcwd %s\n", oldcwd);
		_strcpy(cwd, homevar);
		chdir(cwd);
		getcwd(buffer,1024);
		printf("new cwd is: %s\n", buffer);
		change_pwd(cwd);
		change_oldpwd(oldcwd);
		free(buffer);
		free(oldcwd);
		free(cwd);
		clean_cmd(1, av);
		return;
	}
}
/**
 * change_pwd - updates PWD
 * @pwdpath: new value for pwd
 */
void change_pwd(char *pwdpath)
{
	int i = 0, id = -1;
	char *newpwd = NULL;
	struct stat dircheck;

	if (!pwdpath || stat(pwdpath, &dircheck) != 0)
	{
		printf("dir not existent\n");
		return;
	}

	while (environ[i])
	{
		if (_strncmp(environ[i], "PWD", 3) == 0 &&
			       	(environ[i][3] == '='))
		{
/*			pwdvar = environ[i];
*/			id = i;
			break;
		}
		i++;
	}
	
	newpwd = malloc(_strlen(pwdpath) + _strlen("PWD") + 2);
	_strcpy(newpwd, "PWD");
	_strcat(newpwd, "=");
	_strcat(newpwd, pwdpath);
	_strcpy(environ[id] ,newpwd);
	free(newpwd);
	return;

}

/**
 * change_oldpwd - updates OLDPWD
 * @oldpwdpath: new value for oldpwd
 */
void change_oldpwd(char *oldpwdpath)
{
	int i = 0, id = -1;
	char *new_oldpwd = NULL;
	struct stat dircheck;

	if (!oldpwdpath || stat(oldpwdpath, &dircheck) != 0)
	{
		printf("dir not existent\n");
		return;
	}

	while (environ[i])
	{
		if (_strncmp(environ[i], "OLDPWD", 6) == 0 &&
			       	(environ[i][6] == '='))
		{
			id = i;
			break;
		}
		i++;
	}
	
	
	new_oldpwd = malloc(_strlen(oldpwdpath) + _strlen("OLDPWD") + 2);
	_strcpy(new_oldpwd, "OLDPWD");
	_strcat(new_oldpwd, "=");
	_strcat(new_oldpwd, oldpwdpath);
	_strcpy(environ[id] ,new_oldpwd);
	free(new_oldpwd);
	return;
}


/**
 * get_home : gets the value of the HOME variable
 */
void get_home(char **homevar)
{
	char temp[1024];
	int i = 0, id = -1;

	while (environ[i])
	{
		if (_strncmp(environ[i], "HOME", 4) == 0 &&
			       	(environ[i][4] == '='))
		{
			id = i;
			break;
		}
		i++;
	}
	_strcpy(temp, environ[id]);
	strtok(temp,"=");
	*homevar = strtok(NULL,"=");
	/*printf("%s\n",ret_home);
	*/return;

}
/**
 * get_PWD : gets the value of the PWD variable
 */
