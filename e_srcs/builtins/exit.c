/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 17:54:56 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/02 11:29:14 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	execute_exit(char **args, int *exit_code)
{
	printf("exit\n");
	if (args_len(args) > 1)
	{
		if (is_number(args[1]))
		{
			if (args_len(args) == 2)
				exit(ft_atoi(args[1]));
			else
			{
				write(2, "minishell: exit: too many arguments\n", 37);
				*exit_code = 1;
				return (1);
			}
		}
		else
		{
			write(2, "minishell: exit: ", 18);
			write(2, args[1], ft_strlen(args[1]));
			write(2, ": numeric argument required\n", 29);
			exit(255);
		}
	}
	else
		exit(*exit_code);
}
