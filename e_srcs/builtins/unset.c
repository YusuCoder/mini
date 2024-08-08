/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:39:28 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/08 20:56:16 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to execute the "unset" command
int	remove_env_var(char ***env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return (-1);
	i = 0;
	j = 0;
	while ((*env)[i])
	{
		if (i != index)
		{
			new_env[j] = (*env)[i];
			j++;
		}
		else
			free((*env)[i]);
		i++;
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}

void	execute_unset(char **args, char ***env, int *exit_code)
{
	int		i;
	int		j;
	int		arg_len;

	i = 1;
	if (args[1] == NULL)
		return ;
	while (args[i])
	{
		arg_len = strlen(args[i]);
		j = 0;
		while ((*env)[j])
		{
			if (strncmp((*env)[j], args[i], arg_len) == 0)
				// (*env)[j][arg_len] == '=')
			{
				if (remove_env_var(env, j) != 0)
				{
					write(2, "unset: memory allocation error\n", 31);
					*exit_code = 1;
					return ;
				}
				break ;
			}
			j++;
		}
		i++;
	}
	*exit_code = 0;
}
