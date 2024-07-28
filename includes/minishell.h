/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:04:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/27 19:52:08 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/*---General command struct---*/
typedef struct s_commands
{
	char		**tokens;
	t_ryusupov	**env;
	uint8_t		exit_code;
	int			*pipe;
	int			argc;
	char		**envp;
	char		**path;
}				t_command;

typedef enum s_process
{
	INIT,
	RES,
	CHILD_PROCESS,
}			t_process;

/*----global variable-----*/
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
int		parse(char	**t);
int		count_str(char c);
int		is_empty(const char *str);
int		count_tokens(char token);
/*-----------PARSING-------------*/
void	expand(char	**tokens, t_ryusupov **env);
int		not_in_squote(char *token, int i);
int		is_exeption(char c);
int		still_dollar_sign_there(char *token);
int		expansion_of_first_token(char *token);
char	*dollar_sign(char *sign, char *token, t_ryusupov **env);
char	*remove_var(char *token, char *v_name);
char	*replace_token(char *token, char *e_name);
char	*get_e_name(char *v_name, t_ryusupov **env);
char	*get_v_name(char	*token);
char	*fill_e_name(char *line, int i);
char	*get_c_string(char *token);
char	*get_x_string(char	*token);
int		count_string(char	*token);

/*-------------*/
/*  Executing  */
/*-------------*/
void	execute(t_command *cmd);
int		execute_builtin(t_command *cmd);
int		execute_cd(char **args);
int		execute_pwd(void);
int		execute_echo(char **args);
int		execute_env(char **envp);
int		execute_export(char **args);
int		execute_unset(char **args);
int		execute_exit(void);

#endif
