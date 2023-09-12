#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "hsh.h"

/**
 * _setenv - Implementation of the setenv function
 * @name: Name of entry
 * @val: Value associated with entry
 * @overwrite: condition for overwriting value of entry
 * @cnxt: shell context
 * Return: 0, if successful
 */

int _setenv(
	const char *name,
	const char *val,
	int overwrite,
	context_t *cnxt
)
{
	node_t *var = get_node(cnxt->env, name);

	if (var != NULL && overwrite == 0)
		return (0);

	add_node_end(&cnxt->env, name, val);

	return (1);
}

/**
 * _getenv - get env variable
 *
 * @name: variable name
 * @cnxt: shell context
 *
 * Return: pointer to string, or NULL
 */
char *_getenv(const char *name, context_t *cnxt)
{
	char *ptr = NULL;
	node_t *node;

	node = get_node(cnxt->env, name);
	if (node != NULL)
		ptr = node->val;
	return (ptr);
}

/**
 * _unsetenv - remove env variable
 *
 * @name: variable name
 * @cnxt: shell context
 *
 * Return: 0 on success, 1 on failure
 */
int _unsetenv(const char *name, context_t *cnxt)
{
	return (pop_node(&cnxt->env, name));
}

/**
 * allocate_env - allocate new r/w env
 *
 * @cnxt: shell context
 */
void allocate_env(context_t *cnxt)
{
	int f = 0;
	char *key, *val, *r, *tmp = NULL;

	while (*(environ + f))
	{
		tmp = _strdup(*(environ + f));
		r = tmp;
		key = strtok(tmp, "=");
		if (key != NULL)
		{
			val = strtok(NULL, "=");
			if (val != NULL)
				add_node_end(&cnxt->env, key, val);
		}

		free(r);
		f++;
	}
}
