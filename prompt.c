#include "hsh.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

/**
 * prompt - display prompt if not connected to tty and
 * read line from user.
 *
 * @cnxt: shell context
 * @stream: file descriptor
 *
 * Return: 0 success, nonzero on failure.
 */
int prompt(context_t *cnxt, FILE *stream)
{
	cnxt->isatty = isatty(fileno(stream));
	if (cnxt->isatty)
	{
		_puts("#cProgrammingisfun$ ");
		fflush(stdout);
	}

	if (getline(&cnxt->buff.ptr, &cnxt->buff.len, stream) == EOF)
	{
		return (EOF);
		free_buff(&cnxt->buff);
	}
	return (0);
}
