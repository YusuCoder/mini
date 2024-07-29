/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:11:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 16:07:44 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_builtin(t_command *cmd)
{
	int	is_error;

	is_error = 0;
	if (ft_strcmp(cmd->tokens[0], "pwd") == 0)
		is_error = execute_pwd();
	else if (ft_strcmp(cmd->tokens[0], "cd") == 0)
		is_error = execute_cd(cmd->tokens);
	// else if (ft_strcmp(cmd->tokens[0], "env") == 0)
	// 	is_error = execute_env(cmd->env);
	else if (ft_strcmp(cmd->tokens[0], "echo") == 0)
		is_error = execute_echo(cmd->tokens);
	else if (ft_strcmp(cmd->tokens[0], "unset") == 0)
		is_error = execute_unset(cmd->tokens);
	else if (ft_strcmp(cmd->tokens[0], "export") == 0)
		is_error = execute_export(cmd->tokens);
	else if (ft_strcmp(cmd->tokens[0], "exit") == 0)
		is_error = execute_exit();
	return (is_error);
}


void	execute(t_command *cmd)
{
	int	is_error;

	// cmd->envp = set_envp(cmd->env);
	is_error = execute_builtin(cmd);
}
