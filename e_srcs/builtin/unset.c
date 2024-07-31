/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:39:28 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 21:17:27 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_unset(char **args, int *exit_code)
{
	int i;

	i = 0;
	if (args[1] == NULL)
	{
		write(2, "unset: not enough arguments\n", 28);
		*exit_code = 1;
		return (1);
	}
	while (args[i])
	{
		if (unsetenv(args[1]) != 0)
		{
			perror("unset");
			*exit_code = 1;
			return (1);
		}
		i++;
	}
	*exit_code = 0;
	return (0);
}
