#include "hsh.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * builtin_env - this function prints enviroment variables
 *
 * @cnxt: The shell context
 *
 * Return: 0 always
 */
int builtin_env(context_t *cnxt)
{
	print_list(cnxt->env);
	return (0);
}

/**
 * builtin_exit -This function is to exit builtin command
 *
 * @cnxt:the shell context
 *
 * Return: 0 always
 */
int builtin_exit(context_t *cnxt)
{
	int status = cnxt->status;

	if (cnxt->cmd->args[1] != NULL)
	{
		status = _atoi(cnxt->cmd->args[1]);
		if (status < 0)
		{
			print_err(cnxt, "The number is Illegal");
			puts_err(": ");
			puts_err(cnxt->cmd->args[1]);
			putchar_err('\n');
			status = 2;
		}
	}
	free_cnxt(cnxt);
	exit(status);
	return (0);
}

/**
 * builtin_setenv -this is to change the environmental variable
 *
 * @cnxt:the shell context
 *
 * Return: 0 on success, 1 on error
 */
int builtin_setenv(context_t *cnxt)
{
	char *name = cnxt->cmd->args[1];
	char *val = cnxt->cmd->args[2];

	if (name != NULL && val != NULL)
		return (_setenv(name, val, 1, cnxt));
	return (1);
}

/**
 * builtin_unsetenv - change environmental variable
 *
 * @cnxt:the shell context
 *
 * Return: 0 on success, 1 on error
 */
int builtin_unsetenv(context_t *cnxt)
{
	char *name = cnxt->cmd->args[1];

	if (name != NULL)
		return (_unsetenv(name, cnxt));
	return (1);
}

/**
 * builtin_cd - this command is to change directory
 *
 * @cnxt:the  shell context
 *
 * Return: 0 on success, 1 on error
 */
int builtin_cd(context_t *cnxt)
{
	char *tmp = NULL, *path = NULL;

	if (cnxt->cmd->args[1] == NULL)
		path = _strdup(_getenv("HOME", cnxt));
	else if (*(cnxt->cmd->args[1]) == '-')
	{
		path = _strdup(_getenv("OLDPWD", cnxt));
		_puts(path);
		_putchar('\n');
	}
	else
		path = _strdup(cnxt->cmd->args[1]);
	tmp = getcwd(tmp, 100);
	if (chdir(path) == -1)
	{
		free(path);
		free(tmp);
		return (1);
	}
	_setenv("OLDPWD", tmp, 1, cnxt);
	_setenv("PWD", path, 1, cnxt);

	free(tmp);
	free(path);
	return (0);
}
