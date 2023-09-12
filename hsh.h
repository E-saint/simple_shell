#ifndef HSH_H
#define HSH_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define OP_NONE	0
#define OP_OR	1
#define OP_AND	2

extern char **environ;

/**
 * struct buf - string buffer
 *
 * @ptr: string pointer
 * @len: size of buffer
 */
typedef struct buff
{
	char *ptr;
	size_t len;
} buff_t;

/**
 * struct node - linked list node
 *
 * @key: key of the node
 * @val: node value
 * @next: next node
 */
typedef struct node
{
	char *key;
	char *val;
	struct node *next;
} node_t;

/**
 * struct command - commands to execute in a line
 *
 * @name: command name
 * @args: command arguments
 * @op: operator
 * @next: next command
 */
typedef struct command
{
	char *name;
	char **args;
	char op;
	struct command *next;
} command_t;

/**
 * struct context - context data for our shell
 *
 * @name: name of program according to argv[0]
 * @line: current line number of piped content or file
 * @cmd: parsed list of commands
 * @env: head of the env variables linked list
 * @aliases: head of the alias linkeed list
 * @buff: buffer to store input
 * @status: exit status of the child process
 * @isatty: if current file descriptor is a tty
 */
typedef struct context
{
	char *name;
	size_t line;
	command_t *cmd;
	node_t *env;
	node_t *aliases;
	buff_t buff;
	int status;
	u_int8_t isatty;
} context_t;

/**
 * struct builtin - builtin commands.
 *
 * @name: command name
 * @f: function pointer
 */
typedef struct builtin
{
	char *name;
	int (*f)(context_t *cnxt);
} builtin_t;

/* builtins */
int builtin_env(context_t *cnxt);
int builtin_exit(context_t *cnxt);
int builtin_setenv(context_t *cnxt);
int builtin_unsetenv(context_t *cnxt);
int builtin_cd(context_t *cnxt);
int builtin_alias(context_t *cnxt);

char **split(char *str, char *delim);
char *which(const char *bin, context_t *cnxt);
void print_err(context_t *cnxt, char *err);
int prompt(context_t *cnxt, FILE *stream);

void free_array(char **arr);
void free_buff(buff_t *buff);
void free_cnxt(context_t *cnxt);

int exec_builtin(context_t *cnxt);
ssize_t _getline(char **str, size_t *len, FILE *stream);
int execute(context_t *cnxt);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

void parse_commands(context_t *cnxt, char *input);
void parse_args(context_t *cnxt);
char *to_string(int w);

void allocate_env(context_t *cnxt);
char *_getenv(const char *name, context_t *cnxt);
int _setenv(
	const char *name,
	const char *val,
	int overwrite,
	context_t *cnxt
);
int _unsetenv(const char *name, context_t *cnxt);

/* linked list */
void free_list(node_t **head);
size_t print_list(const node_t *hd);
char **to_array(node_t *hd);
node_t *get_node(node_t *head, const char *key);
size_t pop_node(node_t **head, const char *key);
node_t *add_node_end(node_t **head, const char *key, const char *val);

/* command list */
void free_commands(command_t **head);
void add_command(command_t **head, const char *args, char op);
command_t *next_command(command_t **head);

int _puts(char *str);
int _putchar(char ch);
int puts_err(char *str);
int putchar_err(char ch);

int _atoi(char *str);

int _strcmp(const char *s1, const char *s2);
int _strlen(const char *str);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t w);
char *_strdup(const char *str);

#endif /* HSH_H */
