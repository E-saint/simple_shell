#include "hsh.h"
#include <string.h>
#include <stdio.h>

/**
 * print_alias - print alias set in the shell
 * @alias: It represnts the  alias node
 * node_t: This is a pointer to the parameter
 * val: it represent the value of the struct node
 */
void print_alias(node_t *alias)
{
	_puts(alias->key);
	_putchar('=');
	_putchar('\'');
	_puts(alias->val);
	_putchar('\'');
	_putchar('\n');
}

/**
 * print_aliases - print all the aliases
 * context_t: the pointer to the parameter
 * @cnxt: shell context
 */
void print_aliases(context_t *cnxt)
{
	node_t *alias = cnxt->aliases;

	while (alias)
	{
		print_alias(alias);
		alias = alias->next;
	}
}

/**
 * set_alias - set a new alias
 * @val: alias value
 * @cnxt: the shell context
 * @key: the alias name
 * Return: 0 on success, 1 on failure
 */
int set_alias(context_t *cnxt, const char *key, const char *val)
{
	if (add_node_end(&cnxt->aliases, key, val) == NULL)
		return (1);
	return (0);
}

/**
 * get_alias -this function gets an alias
 * @cnxt:the shell context
 * @key:the alias name
 * Return: node_t pointer or null
 */
node_t *get_alias(context_t *cnxt, const char *key)
{
	return (get_node(cnxt->aliases, key));
}

/**
 * builtin_alias - set or get alias
 * @cnxt: shell context
 * Return: 0 on success, 1 on error
 */
int builtin_alias(context_t *cnxt)
{
	char *token, *tmp, *val, *r;
	char **args = cnxt->cmd->args + 1;

	if (*args == NULL)
		print_aliases(cnxt);

	while (*args)
	{
		tmp = _strdup(*args);
		r = tmp; /* for free() */
		token = strtok(tmp, "=");
		if (token == NULL)
		{
			free(tmp);
			continue;
		}
		val = strtok(NULL, "=");
		if (val == NULL)
			print_alias(get_alias(cnxt, token));
		else
			set_alias(cnxt, token, val);
		free(r);
		args++;
	}

	return (0);
}
