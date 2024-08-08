/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/07 14:37:57 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	change_directory(char *path, int *exit_code)
{
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		*exit_code = 1;
		return (1);
	}
	*exit_code = 0;
	return (0);
}

int	cd_home_dir(char **env, int *exit_code)
{
	char	*home;

	home = get_env_value(env, "HOME");
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		*exit_code = 1;
		return (1);
	}
	return (change_directory(home, exit_code));
}

int	cd_dash_arg(char *prev_dir, int *exit_code)
{
	if (!prev_dir)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 30);
		*exit_code = 1;
		return (1);
	}
	printf("%s\n", prev_dir);
	return (change_directory(prev_dir, exit_code));
}

char	*get_env_value(char **env, const char *key)
{
	int		i;
	size_t	key_len;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0 && env[i][key_len] == '=')
			return (env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

void	execute_cd(char **args, char **env, int *exit_code)
{
	char	*prev_dir;
	char	curr_dir[PATH_MAX];

	prev_dir = get_env_value(env, "OLDPWD");
	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return ;
	}
	if (!args[1] || strcmp(args[1], "~") == 0)
	{
		if (cd_home_dir(env, exit_code) == 0)
			update_pwd_oldpwd(curr_dir, env, exit_code);
	}
	else if (strcmp(args[1], "-") == 0)
	{
		if (cd_dash_arg(prev_dir, exit_code) == 0)
			update_pwd_oldpwd(curr_dir, env, exit_code);
	}
	else
	{
		if (change_directory(args[1], exit_code) == 0)
			update_pwd_oldpwd(curr_dir, env, exit_code);
	}
}
