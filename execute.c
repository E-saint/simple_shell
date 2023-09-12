#include "hsh.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * execute - This function executes a program with arguments
 *
 * @cnxt:The shell context
 *
 * Return: 0 on success, 1 on command not found, -1 on failure
 */
int execute(context_t *cnxt)
{
	char *bin;
	pid_t child_pid;
	int status = 0;
	char **envt = to_array(cnxt->env);

	bin = which(*cnxt->cmd->args, cnxt);
	if (bin == NULL)
	{
		free_array(envt);
		free(bin);
		return (1);
	}

	child_pid = fork();
	if (child_pid == -1)
	{
		free(bin);
		return (-1);
	}
	else if (child_pid == 0)
	{
		if (execve(bin, cnxt->cmd->args, envt) == -1)
			_exit(EXIT_FAILURE);
	}
	else
	{
		if (wait(&status) == -1)
		{
			free_array(envt);
			free(bin);
			return (-1);
		}
		cnxt->status = WEXITSTATUS(status);
	}

	free_array(envt);
	free(bin);
	return (0);
}

/**
 * exec_builtin - To execute a built in command
 *
 * @cnxt:The shell context
 *
 * Return: 0 on success, -1 failure
 */
int exec_builtin(context_t *cnxt)
{
	int f = 0;
	builtin_t bltns[] = {
		{"envt", builtin_env},
		{"exit", builtin_exit},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{"cd", builtin_cd},
		{"alias", builtin_alias},
		{NULL, NULL}
	};

	if (cnxt->cmd->args == NULL)
		return (-1);

	for (; bltns[f].name != NULL; f++)
		if (_strcmp(bltns[f].name, *cnxt->cmd->args) == 0)
			return (bltns[f].f(cnxt));
	return (-1);
}
