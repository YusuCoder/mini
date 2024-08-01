/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:24:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/01 20:27:13 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	print_arg(char *arg, int exit_code)
{
	if (strncmp(arg, "$?", 2) == 0)
	{
		printf("%d", exit_code);
		if (ft_strlen(arg) > 2)
			printf("%s", arg + 2);
	}
	else
		printf("%s", arg);
}

static int is_all_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return 0;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}

static int skip_all_n(char **args, int *i)
{
	int all_n;

	all_n = 0;
	while (args[*i] && is_all_n(args[*i]))
	{
		all_n = 1;
		(*i)++;
	}
	return all_n;
}

int execute_echo(char **args, int *exit_code)
{
	int		new_line;
	int		space;
	int		i;

	new_line = 1;
	space = 0;
	i = 1;
	if (skip_all_n(args, &i))
		new_line = 0;
	while (args[i])
	{
		if (space)
			printf(" ");
		print_arg(args[i], *exit_code);
		space = 1;
		i++;
	}
	if (new_line)
		printf("\n");
	*exit_code = 0;
	return 0;
}
