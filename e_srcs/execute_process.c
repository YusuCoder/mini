/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 12:03:24 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/16 20:41:26 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_child_process(t_data *data, t_cmd *cmd, int *prev_fd)
{
	if (*prev_fd != 1)
	{
		if (dup2(*prev_fd, STDIN_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
		close(*prev_fd);
	}
	if (cmd->next != NULL)
	{
		close(cmd->pipe_fd[0]);
		if (dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
			free_error_exit(data, *data->exit_code, "dup2");
		close(cmd->pipe_fd[1]);
	}
	// handle_redirections(cmd);
	execute_single_command(data, cmd);
	free_exit(data, *data->exit_code);
}

void	run_parent_process(t_cmd *cmd, int *prev_fd)
{
	wait(NULL);
	if (*prev_fd != -1)
	{
		close(*prev_fd);
		*prev_fd = -1;
	}
	if (cmd->next != NULL)
	{
		close(cmd->pipe_fd[1]);
		*prev_fd = cmd->pipe_fd[0];
	}
	else
		*prev_fd = -1;
}
