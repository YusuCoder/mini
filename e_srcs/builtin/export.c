/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:29:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 21:25:08 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_export(t_command *cmd, int *exit_code)
{
	char	*env_line;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	if (cmd->tokens[1] == NULL)
	{
		while (cmd->envp[i])
		{
			env_line = *cmd->envp;
			printf("%s\n", env_line);
			i++;
		}
	}
	else
	{
		while (cmd->tokens[i])
		{
			name = strtok(cmd->tokens[i], "=");
			value = strtok(NULL, "=");
			if (name && value)
			{
				if (setenv(name, value, 1) != 0)
				{
					perror("export");
					*exit_code = 1;
					return (1);
				}
			}
			else
			{
				write(2, "export: invalid argument\n", 25);
				*exit_code = 1;
				return (1);
			}
			i++;
		}
	}
	*exit_code = 0;
	return (0);
}
