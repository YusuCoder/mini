/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/04 18:54:16 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_wrong_command(char *arg)
{
	write(2, "minishell: ", 12);
	write(2, arg, ft_strlen(arg));
	write(2, ": command not found\n", 21);
}

int	execute_builtin(t_command *cmd, char *prev_dir, int prev_dir_size,
	int *exit_code)
{
	if (cmd->tokens[0] == NULL)
	{
		*exit_code = 0;
		return (0);
	}
	if (ft_strcmp(cmd->tokens[0], "pwd") == 0)
		return (execute_pwd(exit_code));
	else if (ft_strcmp(cmd->tokens[0], "cd") == 0)
		return (execute_cd(cmd, prev_dir, prev_dir_size, exit_code));
	else if (ft_strcmp(cmd->tokens[0], "env") == 0)
		return (execute_env(cmd->envp, exit_code));
	else if (ft_strcmp(cmd->tokens[0], "echo") == 0)
		return (execute_echo(cmd->tokens, exit_code));
	else if (ft_strcmp(cmd->tokens[0], "unset") == 0)
		return (execute_unset(cmd->tokens, exit_code));
	else if (ft_strcmp(cmd->tokens[0], "export") == 0)
		return (execute_export(cmd, exit_code));
	else if (ft_strcmp(cmd->tokens[0], "exit") == 0)
		return (execute_exit(cmd->tokens, exit_code));
	else
	{
		print_wrong_command(cmd->tokens[0]);
		*exit_code = 127;
		return (127);
	}
}

int	execute(t_command *cmd, char *prev_dir, int prev_dir_size, int *exit_code)
{
	return (execute_builtin(cmd, prev_dir, prev_dir_size, exit_code));
}
