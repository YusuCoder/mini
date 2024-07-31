/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:24:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/31 12:42:15 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*substitute_vars(char *arg, int exit_code)
{
	static char	code_str[12];

	if (ft_strcmp(arg, "$?") == 0)
	{
		snprintf(code_str, sizeof(code_str), "%d", exit_code);
		return (code_str);
	}
	return (arg);
}

int	execute_echo(char **args, int exit_code, int *exit_code_out)
{
	int		new_line;
	int		i;
	char	*arg;

	new_line = 1;
	i = 1;
	if (args[i] && ft_strcmp(args[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (args[i])
	{
		arg = substitute_vars(args[i], exit_code);
		if (i > 1) printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (new_line) printf("\n");
	*exit_code_out = 0;
	return (0);
}
