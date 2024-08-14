/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:20:07 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/14 12:13:42 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_tokens(t_data *data)
{
	free_array(data->tokens);
	data->tokens = NULL;
	free_list(&data->cmd_list);
}

void	print_wrong_command(char *arg, int *exit_code)
{
	ft_perror("minishell: ", arg, ": command not found");
	*exit_code = 127;
}

void	execute_builtin(t_data *data, char **args, char ***env, int *exit_code)
{
	int	result;

	result = 0;
	if (is_cd(args[0]))
		result = execute_cd(args, *env, exit_code);
	else if (is_pwd(args[0]))
		result = execute_pwd(exit_code);
	else if (is_env(args[0]))
		result = execute_env(*env, exit_code);
	else if (is_echo(args[0]))
		result = execute_echo(args, exit_code);
	else if (ft_strcmp(args[0], "export") == 0)
		result = execute_export(args, env, exit_code);
	else if (ft_strcmp(args[0], "unset") == 0)
		result = execute_unset(args, env, exit_code);
	else if (ft_strcmp(args[0], "exit") == 0)
		execute_exit(data, args, exit_code);
	if (result == -1)
		free_exit(data, *exit_code);
}

void	execute(t_data *data)
{
	t_cmd	*current;

	current = data->cmd_list;
	// if (data->cmd_num == 1)
	// {
	// 	if (is_builtin(data->cmd_list->args[0]))
	// 		execute_builtin(data->cmd_list->args, &data->env, data->exit_code);
	// 	else if (data)
	// }
	while (current != NULL)
	{
		if (current->args[0] == NULL)
			data->exit_code = 0;
		else if (is_builtin(current->args[0]))
			execute_builtin(data, current->args, &data->env, data->exit_code);
		else
			print_wrong_command(current->args[0], data->exit_code);
		current = current->next;
		clean_tokens(data);
	}
}

// void	execute(t_command *cmd, int *exit_code)
// {
// 	if (cmd->tokens[0] == NULL)
// 		*exit_code = 0;
// 	else if (is_builtin(cmd->tokens[0]))
// 		execute_builtin(cmd->tokens, &cmd->envp, exit_code);
// 	else
// 		print_wrong_command(cmd->tokens[0], exit_code);
// }

// void	execute(t_command *cmd, int *exit_code)
// {
// 	int i = 0;
// 	while (cmd->sub_command->sub_cmd_array[i])
// 	{
// 		printf("%s\n", cmd->sub_command->sub_cmd_array[i]);
// 		i++;
// 	}
// 	if (cmd->tokens[0] == NULL)
// 		*exit_code = 0;
// 	else if (is_builtin(cmd->tokens[0]))
// 		execute_builtin(cmd->tokens, &cmd->envp, exit_code);
// 	else
// 		print_wrong_command(cmd->tokens[0], exit_code);
// }
