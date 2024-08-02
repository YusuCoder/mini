
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

/*----global variable-----*/ // <------- !!! DON"T FORGET TO CHANGE !!!
t_command	gl_command;

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
/*----------envp handling-----------*/
// char	**set_envp(t_ryusupov **envp);
char	**set_envp(char **envp);
// int		get_len(t_ryusupov **str);
int		get_len(char **envp);
/*-------------*/
/*  Executing  */
/*-------------*/
int		execute(t_command *cmd, char *prev_dir, int prev_dir_size, int *exit_code);
int		execute_builtin(t_command *cmd, char *prev_dir, int prev_dir_size, int *exit_code);
int		execute_cd(t_command *cmd, char *prev_dir, int prev_dir_size, int *exit_code);
int		cd_home_dir(char *arg, char **env, int *exit_code);
int		cd_dash_arg(char *arg, char *prev_dir, int *exit_code);
int		change_directory(char *arg, char *path, int *exit_code);
void	update_env(char *prev_dir, char **env, int *exit_code);
int		execute_pwd(int *exit_code);
int		execute_echo(char **args, int *exit_code);
int		execute_env(char **env, int *exit_code);
int		execute_export(t_command *cmd, int *exit_code);
int		execute_unset(char **args, int *exit_code);
int		execute_exit(char **args, int *exit_code);

#endif
