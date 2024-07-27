/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:11:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/27 17:12:36 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(char **args)
{
	int	is_error;

	if (ft_strcmp(args[0], "pwd") == 0)
		is_error = execute_pwd(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		is_error = execute_cd(args);
	else if (ft_strcmp(args[0], "env") == 0)
		is_error = execute_env(args);
	else if (ft_strcmp(args[0], "echo") == 0)
		is_error = execute_echo(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		is_error = execute_unset(args);
	else if (ft_strcmp(args[0], "export") == 0)
		is_error = execute_export(args);
	else if (ft_strcmp(args[0], "exit") == 0)
		is_error = execute_exit(args);
	return (is_error);
}
void	execute(char **args)
{
	int	is_error;

	is_error = execute_builtin(args);
}
