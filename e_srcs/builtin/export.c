/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:29:38 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/28 17:40:21 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_export(char **args)
{
	char	*env_var;
	char	*name;
	char	*value;

	if (args[1] == NULL)
	{
		write(2, "export: expected arguments\n", 28);
		return (0);
	}
	env_var = args[1];
	name = strtok(env_var, "=");
	value = strtok(NULL, "=");
	if (name && value)
	{
		if (setenv(name, value, 1) != 0)
			perror("export");
	}
	else
		write(2, "export: invalid fromat, expected NAME=VALUE\n", 45);
	return (0);
}
