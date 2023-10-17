#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM "\t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @func: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*func)(data_shell *datash);
} builtin_t;

/* lists1.c */
sep_list *add_sep_nodeEnd(sep_list **head, char sep);
void free_sep_list(sep_list **head);
line_list *add_line_nodeEnd(line_list **head, char *line);
void free_line_list(line_list **head);

/* lists2.c */
r_var *add_var_node(r_var **head, int lvar, char *var, int lval);
void free_var_list(r_var **head);

/* str_func1.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *str, char chr);
int _strspn(char *str, char *accept);

/* str_func2.c */
char *_strdup(const char *str);
int _strlen(const char *str);
int cmp_chars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *str);
void rev_string(char *str);

/* memory.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);


/* check_syntax_error.c */
int repeated_char(char *input, int idx);
int error_sep(char *input, int idx, char last);
int first_char(char *input, int *idx);
void printSyntaxError(data_shell *datash, char *input, int idx, int boolean);
int checkSyntaxError(data_shell *datash, char *input);

/* shell_loop.c */
char *withoutComment(char *input);
void shellLoop(data_shell *datash);

/* read_line.c */
char *read_line(int *i_eof);

/* split.c */
char *swap_char(char *input, int boolean);
void add_nodes(sep_list **head_s, line_list **head_l, char *input);
void go_next(sep_list **list_s, line_list **list_l, data_shell *datash);
int split_commands(data_shell *datash, char *input);
char **split_line(char *input);

/* replace_var.c */
void checkEnv(r_var **head, char *input, data_shell *data);
int checkVars(r_var **head, char *in, char *st, data_shell *data);
char *replacedInput(r_var **head, char *input, char *new_input, int new_len);
char *rep_var(char *input, data_shell *datash);

/* get_line.c */
void bring_line(char **lineptr, size_t *n, char *buffer, size_t buff);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);

/* exec_line */
int exec_line(data_shell *datash);

/* execmd.c */
int is_cdir(const char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(data_shell *datash);
int check_error_cmd(char *dir, data_shell *datash);
int cmd_exec(data_shell *datash);

/* env1.c */
char *_getenv(const char *name, char **_environ);
int _env(data_shell *datash);

/* env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, data_shell *datash);
int _cmpenv(data_shell *datash);
int _unsetenv(data_shell *datash);

/* get_dir.c */
void cdDot(data_shell *datash);
void cdTo(data_shell *datash);
void cdPrevious(data_shell *datash);
void cdToHome(data_shell *datash);

/* cd_shell.c */
int cdShell(data_shell *datash);

/* builtin.c */
int (*getBuiltin(char *cmd))(data_shell *datash);

/* exit_shell.c */
int exitShell(data_shell *datash);

/* stdlib.c */
int getLen(int n);
char *auxItoa(int n);
int _atoi(char *s);

/* error1.c */
char *strcat_cd(data_shell *, char *, char *, char *);
char *error_get_cd(data_shell *datash);
char *error_not_found(data_shell *datash);
char *error_exit_shell(data_shell *datash);

/* error2.c */
char *error_get_alias(char **args);
char *error_env(data_shell *datash);
char *error_syntax(char **args);
char *error_permission(char **args);
char *errorPath126(data_shell *datash);


/* get_error.c */
int get_error(data_shell *datash, int eval);

/* get_sign.c */
void get_sign(int signal);

/* help1.c */
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_general(void);
void help_exit(void);

/* help2.c */
void help(void);
void help_alias(void);
void help_cd(void);

/* get_help.c */
int get_help(data_shell *datash);

#endif /* _SHELL_H_ */
