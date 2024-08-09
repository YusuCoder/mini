
#ifndef MINISHELL_H
# define MINISHELL_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[24m"
# define MAGENTA "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[97m"
# define RESET "\x1b[0m"

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<signal.h>
#include<string.h>
#include<termios.h>

#define PIPE 124
#define LESS 60
#define GREATER 62
#define AMP 38
#define SQUOTE 39
#define DQUOTE 34

#ifndef TAB
#define TAB 9
#endif

#ifndef SPACE
#define SPACE 32
#endif

#include "../libft/libft.h"

/*---Struct for files and fd---*/
typedef struct s_fd
{
	char	*file;
	int		fd;
}			t_fd;

typedef struct s_sub_commands
{
	char	**sub_cmd_array; //avlue of arguments (commands) each sub-command has
	int		sub_argc_count; //number of arguments (commands) each sub-command has
	char	**arguments;
	int		argc;
	char	**argv;
	t_fd	input_fd;
	t_fd	output_fd;
	t_fd	error_fd;
	int		is_heredoc;
	char	*is_delimeter;
	int		append;
	int		pid;
}			t_sub_commands;

/*---General command struct---*/
typedef struct s_commands
{
	char			**tokens;
	t_ryusupov		**env;
	uint8_t			exit_code;
	int				*pipe;
	int				cmd_num; //number of commands separated with pipe
	char			**envp;
	char			**path;
	t_sub_commands	*sub_command; //array of sub-commands seperated with pipes
}					t_command;
typedef enum s_process
{
	INIT,
	RES,
	CHILD_PROCESS,
}			t_process;

/*----global variable-----*/
t_command	gl_command; // <------- !!! DON"T FORGET TO CHANGE !!!

/*-----------SIGNALS----------*/
void	_init_terminal(t_command *cmd, char **envp);
void	_handle_signals(t_process stats);
/*--------Error messages---------*/
void	_err_msg(char *msg, char err_code);
void	_free_it(char **p);
/*----------TOKENIZING-----------*/
char	**tokenizing(const char *str);
int		take_tokens(char **token, const char *str, int counter, int i);
int		matching_quotes(const char *str);
int		count_words(const char *str, int i);
int		count_tokens(char token);
int		get_word_len(const char *str, int i);
int		count_str(char c);
/*-----------PARSING-------------*/
int		parse(char	**t);
int		check_beginning_and_end(char **t, int i);
int		parse_redirs(char *current, char *next);
int		count_str(char c);
int		quotes_check(char *t);
int		is_empty(const char *str);
/*------------EXPANDING------------*/
// void	expand(char	**tokens, char **env);
void 	expand(char **tokens, char **env, t_command *cmd);
int		not_in_squote(char *token, int i);
int		is_exeption(char c);
int		still_dollar_sign_there(char *token);
int		expansion_of_first_token(char *token);
// char	*dollar_sign(char *sign, char *token, char **env);
char 	*dollar_sign(char *sign, char *token, char **env, t_command *cmd);
char	*remove_var(char *token, char *v_name);
char	*replace_token(char *token, char *e_name);
// char	*get_e_name(char *v_name, t_ryusupov **env);
char 	*get_e_name(char *v_name, char **env);
char	*get_v_name(char	*token);
char	*fill_e_name(char *line, int i);
char	*get_c_string(char *token);
char	*get_x_string(char	*token);
int		count_string(char	*token);
/*------------Sub command bouilding-------------*/
void	sub_cmds_array(t_command *cmd, char **tokens);
int		count_commands(char **tokens, t_command *cmd);
int		count_cmds(char	**token);
int		token_count(t_command *cmd, char **tokens, int i, int j);
int		build_cmds(char	**tokens, t_command *cmd);

/*------------------------*/
/*  Environment handling  */
/*------------------------*/
char	**env_set(char **env);
int		env_len(char **env);
// char	**set_envp(t_ryusupov **envp);
// int		get_len(t_ryusupov **str);
char	*env_var_create(const char *name, const char *value);
int		env_var_find(char **env, const char *name);
int		env_var_add(char ***env, char *new_env_var);
int		env_var_remove(char ***env, int index);
char	*env_value_get(char **env, const char *key);
void	env_value_delete(char **env, char *name);
void	env_value_change(char **env, const char *name, const char *value);
void	env_value_change_pwd_oldpwd(char *prev_dir, char **env, int *exit_code);
char	**env_sort(char **env);
void	quicksort(char **arr, int low, int high);
int		partition(char **arr, int low, int high);
void	swap(char **a, char **b);

/*-------------*/
/*  Executing  */
/*-------------*/
void	execute(t_command *cmd, int *exit_code);
void	print_wrong_command(char *arg, int *exit_code);

/*--------------------*/
/*  Builtin commands  */
/*--------------------*/
void	execute_builtin(char **args, char ***env, int *exit_code);
int		is_builtin(char *arg);
int		is_cd(char *arg);
int		is_pwd(char *arg);
int		is_env(char *arg);
int		is_echo(char *arg);

/*---- cd command ----*/
void	execute_cd(char **args, char **env, int *exit_code);
int		cd_home_dir(char **env, int *exit_code);
int		cd_dash_arg(char *prev_dir, int *exit_code);
int		change_directory(char *path, int *exit_code);

/*---- echo command ----*/
void	execute_echo(char **args, int *exit_code);
int		echo_skip_all_n(char **args, int *i);
int		echo_is_all_n(char *arg);
void	echo_print_arg(char *arg, int exit_code);

/*---- env command ----*/
void	execute_env(char **env, int *exit_code);

/*---- exit command ----*/
void	execute_exit(char **args, int *exit_code);
int		args_len(char **args);
int		is_number(char *arg);

/*---- export command ----*/
void	execute_export(char **args, char ***env, int *exit_code);
void	export_no_args(char **env, int *exit_code);
void	export_with_args(char *arg, char ***env, int *exit_code);
void	export_arg_with_value(char *arg, char *equal_sign,
			char ***env, int *exit_code);
void	export_arg_no_value(char *arg, char ***env, int *exit_code);
int		export_update_env(char ***env, const char *name, const char *value, int overwrite);

/*---- pwd command ----*/
void	execute_pwd(int *exit_code);

/*---- unset command ----*/
void	execute_unset(char **args, char ***env, int *exit_code);

/*--------------------*/
/*  Custom finctions  */
/*--------------------*/
char	*my_strndup(const char *str, int len);
void	*my_realloc(void *ptr, int old_size, int new_size);

#endif
