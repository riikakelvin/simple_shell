#ifndef _SHELL_H
#define _SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

/*Memory Alloc Buffers */
#define R_BUFF_SIZE 1024
#define WR_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define MAX_HIST       4096
#define HIST_FILE	".simple_shell_hist"

/*WHEN USING GETLINE FUCNTION CALL*/
#define USE_GETLINE 0
#define USE_STRTOK 0

/*CHAINING OF COMMANDS IN PROGRAM*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2	
extern char **environ;


/**
 * struct liststr - the  singly linked list
 * @num: the number of field
 * @str: the string
 * @next: refers to the following node
 */
typedef struct liststr
{
	char *str;
	int num;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - includes pseudo-arguements to parse to a function
 *@arg: a string generated from getline containing arguements
 *@argv: array of strings generated from arg
 *@path: a string path for ongoing command
 *@argc: count of the arguement
 *@line_count: the error count
 *@err_num: error code for exit function
 *@history: history node
 *@alias: alias node
 *@env_changed: owhen the environ is changed
 *@status: returns the status of the last executed command
 *@cmd_buff: address of pointer to cmd_buff, when chaining
 *@cmd_buff_type: inclusive of ||, &&, ;
 *@readfd: filedescriptor, source of the line input
 *@histcount: counts of the history line number
 *@linecount_flag: if on count, referes to the input line
 *@fname: filename
 *@env: linked list, a local copy of the environ
 *@environ: custom copy of the environ from LL env
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	char **environ;
	char *fname;
	int argc;
	int err_num;
	int linecount_flag;
	int env_changed;
        int status;
	list_t *env;
	list_t *history;
	list_t *alias;
	unsigned int line_count;

	char **cmd_buff;
	int cmd_buff_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - includes builtin strings & corresponding functions
 *@type: a builtin command flag
 *@func: the function in play
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int main(int ac, char **av);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);
int is_cmd(info_t *, char *);
int find_builtin(info_t *);
int hsh(info_t *, char **);
void find_cmd(info_t *);
void fork_cmd(info_t *);
void _eputs(char *);
int _eputchar(char);
int _putsfd(char *str, int file_d);
int _putfd(char c, int file_d);
int _putchar(char);
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcpy(char *, char *);
char *_strcat(char *, char *);
char *_strdup(const char *);
void _puts(char *);
void _eputs(char *);

char *_strchr(char *, char);
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);

char **strtow1(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

int bfree(void **);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(info_t *);
int loophsh(char **);

char *convert_number(long int, int, int);
int _erratoi(char *);
int print_d(int, int);
void print_error(info_t *, char *);
void remove_comments(char *);

int _mycd(info_t *);
int _myexit(info_t *);
int _myhelp(info_t *t);

int _myalias(info_t *);
int _myalias(info_t *);

int _getline(info_t *, char **, size_t *);
ssize_t get_input(info_t *);
void sigintHandler(int);

void clear_info(info_t *);
void free_info(info_t *, int);
void set_info(info_t *, char **);

char *_getenv(info_t *, const char *);
int _mysetenv(info_t *);
int populate_env_list(info_t *);
int _myenv(info_t *);
int _mysetenv(info_t *);

int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);
char **get_environ(info_t *);

char *get_history_file(info_t *info);
int build_history_list(info_t *info, char *buff, int linecount);
int read_history(info_t *info);
int renumber_history(info_t *info);
int write_history(info_t *info);

list_t *add_node(list_t **, const char *, int);
list_t *node_to_start_with(list_t *, char *, char);
list_t *add_the_node_end(list_t **, const char *, int);
char **list_to_strings(list_t *);
size_t print_list_str(const list_t *);
int delete_the_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
size_t print_list(const list_t *);
ssize_t get_the_node_index(list_t *, list_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int is_chain(info_t *, char *, size_t *);
int replace_string(char **, char *);
int is_chain(info_t *, char *, size_t *);
int replace_vars(info_t *);

void print_first_prompt(char*av, char **env);
pid_t fork(void);


#endif
