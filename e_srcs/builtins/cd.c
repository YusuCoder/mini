/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/31 19:36:24 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to update PWD and OLDPWD in the environment
int	update_env_pwd_oldpwd(char *prev_dir, char **env, int *exit_code)
{
	char	curr_dir[PATH_MAX];
	int		i;

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (1);
	}
	i = -1;
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", ft_strlen("PWD=")) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("PWD=", curr_dir);
		}
		else if (ft_strncmp(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 0)
		{
			free(env[i]);
			env[i] = ft_strjoin("OLDPWD=", prev_dir);
		}
	}
	*exit_code = 0;
	return (0);
}

// Function to change directory and handle errors
int	change_directory(char **args, char *path, int *exit_code)
{
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 16);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 29);
		*exit_code = 1;
		return (1);
	}
	return (0);
}

// Function to handle the "cd -" argument
int	cd_dash_arg(char **args, char *prev_dir, int *exit_code)
{
	if ((ft_strncmp(args[1], "-", 1) == 0) && (prev_dir[0] == '\0'))
	{
		write(2, "minishel: cd: OLDPWD not set\n", 30);
		*exit_code = 1;
		return (1);
	}
	else if (ft_strlen(args[1]) > 1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, &args[1][0], 1);
		write(2, &args[1][1], 1);
		write(2, ": invalid option\n", 18);
		write(2, "cd: usage: cd [-L|-P] [dir]\n", 29);
		*exit_code = 1;
		return (1);
	}
	else
	{
		printf("%s\n", prev_dir);
		return (change_directory(args, prev_dir, exit_code));
	}
}

// Function to handle the "cd" command to change to HOME directory
int	cd_home_dir(char **args, char **env, int *exit_code)
{
	char	*home;
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME", 4) == 0 && env[i][4] == '=')
		{
			home = (env[i] + 5);
			break ;
		}
		else
			home = "";
		i++;
	}
	if (home == NULL || *home == '\0')
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		*exit_code = 1;
		return (1);
	}
	return (change_directory(args, home, exit_code));
}

// Function to execute the "cd" command
int	execute_cd(t_command *cmd, char *prev_dir, int prev_dir_size,
	int *exit_code)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (1);
	}
	if (cmd->tokens[1] == NULL || ft_strcmp(cmd->tokens[1], "~") == 0)
	{
		if (cd_home_dir(cmd->tokens, cmd->envp, exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	else if (cmd->tokens[1][0] == '-')
	{
		if (cd_dash_arg(cmd->tokens, prev_dir, exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	else
	{
		if (change_directory(cmd->tokens, cmd->tokens[1], exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	update_env_pwd_oldpwd(prev_dir, cmd->envp, exit_code);
	return (*exit_code);
}
