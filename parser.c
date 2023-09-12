#include "hsh.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * parse_commands - parse arguments to commands
 *
 * @cnxt: shell context
 * @input: string to parse arguments
 */
void parse_commands(context_t *cnxt, char *input)
{
	char **r = NULL;
	char **cmds = split(input, ";");

	r = cmds;
	while (*cmds)
	{
		add_command(&cnxt->cmd, *cmds, OP_NONE);
		cmds++;
	}
	free_array(r);
}

/**
 * parse_args - parse arguments replace $ variables
 *
 * @cnxt: shell context
 */
void parse_args(context_t *cnxt)
{
	node_t *node;
	char **r = cnxt->cmd->args, *name, *val;

	if (r == NULL)
		return;

	node = get_node(cnxt->aliases, *r);
	/* get alias recursively this could be an alias of alias */
	while (node != NULL)
	{
		free(*r);
		*r = _strdup(node->val);
		node = get_node(cnxt->aliases, *r);
	}
	while (*r)
	{
		if (*r[0] == '$')
		{
			name = (*r) + 1;
			switch (*name)
			{
				case '$':
					val = to_string(getpid());
					break;
				case '?':
					val = to_string(cnxt->status);
					break;
				case '\0':
					r++;
					continue;
				default:
					val = _strdup(_getenv(name, cnxt));
			}
			free(*r);
			*r = _strdup(val);
			free(val);
		}
		r++;
	}
}
