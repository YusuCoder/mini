/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:04:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/16 18:03:14 by ryusupov         ###   ########.fr       */
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

typedef struct s_commands
{
	char		**tokens;
	t_ryusupov	**env;
	uint8_t		exit_code;

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
int		count_words(const char *str, int i);
int		count_tokens(char token);
int		get_word_len(const char *str, int i);
int		count_str(char c);
#endif
