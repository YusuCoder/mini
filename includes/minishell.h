/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:04:06 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/08 17:47:11 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<limits.h>
#include<readline/readline.h>
#include<readline/history.h>

#include "../libft/libft.h"

typedef struct s_commands
{
	char		**tokens;
	t_ryusupov	**env;

}				t_command;


#endif
