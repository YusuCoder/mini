/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 19:21:44 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



static char	*get_env_var(const char *name)
{
	char	*value;

	value = getenv(name);
	if (value)
		return (value);
	else
		return ("");
}

int	execute_cd(char **args)
{
	static char	prev_dir[1024];
	char		curr_dir[1024];
	char		*home;

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		return (1);
	}
	if (args[1] == NULL)
	{
		home = get_env_var("HOME");
		if (home == NULL || *home == '\0')
			write(2, "cd: expected arguments to \"cd\"\n", 32);
		else if (chdir(home) != 0)
			perror("cd");
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		if (prev_dir[0] == '\0')
			write(2, "cd: OLDPWD not set\n", 19);
		else
		{
			printf("%s\n", prev_dir);
			if (chdir(prev_dir) != 0)
				perror("cd");
		}
	}
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	ft_strlcpy(prev_dir, curr_dir, sizeof(prev_dir));
	return (0);
}
