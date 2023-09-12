#include "hsh.h"
#include <stdlib.h>

/**
 * to_array - node list to array
 *
 * @hd: head node
 *
 * Return: array ponter or null
 */
char **to_array(node_t *hd)
{
	char **arr = NULL;
	node_t *node = hd;
	int f = 0;

	arr = malloc(sizeof(char *) * 1);
	while (node != NULL)
	{
		arr = _realloc(arr, sizeof(char *) * (f + 1), sizeof(char *) * (f + 2));
		arr[f] = malloc(
			sizeof(char) * (_strlen(node->key) + _strlen(node->val) + 2)
		);
		arr[f] = _strcpy(arr[f], node->key);
		arr[f] = _strcat(arr[f], "=");
		arr[f] = _strcat(arr[f], node->val);
		node = node->next;
		f++;
	}
	arr[f] = NULL;

	return (arr);
}

/**
 * print_list - prints all the elements of a node_t list.
 *
 * @hd: list to print
 *
 * Return: the number of nodes
 */
size_t print_list(const node_t *hd)
{
	int len = 0;
	const node_t *node = hd;

	while (node != NULL)
	{
		_puts(node->key);
		_putchar('=');
		_puts(node->val);
		_putchar('\n');
		len++;
		node = node->next;
	}

	return (len);
}

/**
 * get_node - returns node with key
 *
 * @head: start node
 * @key: key to check
 *
 * Return: the nth node
 */
node_t *get_node(node_t *head, const char *key)
{
	node_t *node = head;

	while (node != NULL && _strcmp(key, node->key) != 0)
	{
		node = node->next;
	}
	return (node);
}

/**
 * pop_node - remove a node
 *
 * @head: start node
 * @key: key to check
 *
 * Return: 0 on success, 1 on failure
 */
size_t pop_node(node_t **head, const char *key)
{
	size_t f = 0;
	node_t *tmp, *old = NULL;

	tmp = *head;
	while (tmp != NULL && _strcmp(key, tmp->key) != 0)
	{
		old = tmp;
		tmp = tmp->next;
		f++;
	}
	if (tmp == NULL)
		return (1);
	if (old != NULL)
		old->next = tmp->next;
	else
		*head = tmp->next;
	free(tmp->key);
	free(tmp->val);
	free(tmp);
	return (0);
}

/**
 * add_node_end - adds a new node at the end of a listint_t list.
 *
 * @head: start node of the list
 * @key: node key
 * @val: node value
 *
 * Return: the address of the new element, or NULL if it failed
 */
node_t *add_node_end(node_t **head, const char *key, const char *val)
{
	node_t *new, *tmp;

	new = malloc(sizeof(node_t));
	if (new == NULL)
		return (NULL);
	new->key = _strdup(key);
	new->val = _strdup(val);
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	tmp = *head;
	while (tmp->next != NULL && _strcmp(key, tmp->key) != 0)
	{
		tmp = tmp->next;
	}
	if (_strcmp(key, tmp->key) == 0)
	{
		free_list(&new);
		free(tmp->val);
		tmp->val = _strdup(val);
		new = tmp;
	}
	else
	{
		tmp->next = new;
	}

	return (new);
}
