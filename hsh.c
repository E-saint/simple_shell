#include "hsh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

/**
 * handler - handle system signals
 *
 * @no: signal number
 */
void handler(int no)
{
	(void)no;
	if (isatty(fileno(stdin)))
	{
		_puts("\n#cProgrammingisfun$ ");
		fflush(stdout);
	}
}

/**
 * evaluate -the function evaluates input
 *
 * @cnxt:the shell context
 *
 * Return: exit value
 */
int evaluate(context_t *cnxt)
{
	char op, *line = cnxt->buff.ptr;
	int f, exit = 0;
	command_t *cmd = NULL;

	(cnxt->line)++;
	parse_commands(cnxt, strtok(line, "\n"));
	while (cnxt->cmd)
	{
		parse_args(cnxt);
		if (exec_builtin(cnxt) == -1 && cnxt->cmd != NULL)
		{
			f = execute(cnxt);
			if (f == 1)
			{
				cnxt->status = 127;
				print_err(cnxt, "It is not found\n");
			}
			else if (f == -1)
				exit = 1;
		}
		cmd = next_command(&cnxt->cmd);
		op = cmd->op;
		free_commands(&cmd);
		if (op == OP_AND && cnxt->status)
			break;
	}
	return (exit);
}

/**
 * main - entry point for simple shell
 *
 * @ac: argument count
 * @av: arguments array
 *
 * Return: 0 on success, non-zero on failure
 */
int main(int ac, char *av[])
{
	int if_exit = 0, fd = 0;
	context_t cnxt = { NULL, 0,  NULL, NULL, NULL, { NULL, 0 }, 0, 0};
	FILE *stream;

	cnxt.name = av[0];

	if (ac >= 2)
	{
		fd = open(av[1], O_RDONLY);

		if (fd < 0)
		{
			print_err(&cnxt, "It Can't open ");
			puts_err(av[1]);
			putchar_err('\n');
			exit(127);
		}
		stream = fdopen(fd, "p");
	}

	else
		stream = stdin;
	signal(SIGINT, &handler);
	allocate_env(&cnxt);

	do {
		free_buff(&cnxt.buff);
		if (prompt(&cnxt, stream) == EOF)
		{
			if (cnxt.isatty)
				_puts("\n");
			if_exit = 1;
		}
		else if (cnxt.buff.ptr != NULL)
			if_exit = evaluate(&cnxt);
	} while (!if_exit);
	free_cnxt(&cnxt);
	fclose(stream);
	return (cnxt.status);
}
