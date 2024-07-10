/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:04:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/10 13:49:08 by ryusupov         ###   ########.fr       */
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

#include "../libft/libft.h"
/*----global variable-----*/
// t_command	gl_command;
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

t_command	gl_command;

/*-------Function declarations---------*/
void	_init_cmd(t_command *cmd, char **envp);
void	_handle_signals(t_process stats);

#endif
