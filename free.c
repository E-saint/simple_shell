#include "hsh.h"
#include <stdlib.h>

/**
 * free_list - the function frees a node_t list.
 *
 * @head:the  pointer to head node in the list to free
 */
void free_list(node_t **head)
{
	node_t *tmp;

	if (head != NULL)
	{
		while (*head != NULL)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp->key);
			free(tmp->val);
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * free_array -this function free a memory allocated array
 *
 * @arr:array terminated  by NULL
 */
void free_array(char **arr)
{
	int f = 0;

	if (arr != NULL)
	{
		while (arr[f] != NULL)
			free(arr[f++]);
		free(arr);
	}
}

/**
 * free_buff -The function free a buffer
 *
 * @buff: buffer to be fred
 */
void free_buff(buff_t *buff)
{
	free(buff->ptr);
	buff->ptr = NULL;
	buff->len = 0;
}

/**
 * free_cnxt - free the context variable
 *
 * @cnxt: context varible to free
 */
void free_cnxt(context_t *cnxt)
{
	free_buff(&cnxt->buff);
	free_list(&cnxt->env);
	free_list(&cnxt->aliases);
	free_commands(&cnxt->cmd);
}
