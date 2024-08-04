/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:49:51 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/04 15:07:04 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Function to update PWD and OLDPWD in the environment
void	cd_update_pwd_oldpwd(char *prev_dir, char **env, int *exit_code)
{
	char	curr_dir[PATH_MAX];
	int		i;

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
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
}

// Function to change directory and handle errors
int	cd_chdir(char *arg, char *path, int *exit_code)
{
	if (chdir(path) != 0)
	{
		write(2, "minishell: cd: ", 16);
		write(2, arg, ft_strlen(arg));
		write(2, ": No such file or directory\n", 29);
		*exit_code = 1;
		return (1);
	}
	*exit_code = 0;
	return (0);
}

// Function to handle the "cd -" argument
int	cd_dash_arg(char *arg, char *prev_dir, int *exit_code)
{
	if ((ft_strncmp(arg, "-", 1) == 0) && (prev_dir[0] == '\0'))
	{
		write(2, "minishel: cd: OLDPWD not set\n", 30);
		*exit_code = 1;
		return (1);
	}
	else if (ft_strlen(arg) > 1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, &arg[0], 1);
		write(2, &arg[1], 1);
		write(2, ": invalid option\n", 18);
		write(2, "cd: usage: cd [-L|-P] [dir]\n", 29);
		*exit_code = 1;
		return (1);
	}
	else
	{
		printf("%s\n", prev_dir);
		return (cd_chdir(arg, prev_dir, exit_code));
	}
}

// Function to handle the "cd" command to change to HOME directory
int	cd_home_dir(char *arg, char **env, int *exit_code)
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
	return (cd_chdir(arg, home, exit_code));
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
		if (cd_home_dir(cmd->tokens[1], cmd->envp, exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	else if (cmd->tokens[1][0] == '-')
	{
		if (cd_dash_arg(cmd->tokens[1], prev_dir, exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	else
	{
		if (cd_chdir(cmd->tokens[1], cmd->tokens[1], exit_code) == 0)
			ft_strlcpy(prev_dir, curr_dir, prev_dir_size);
	}
	cd_update_pwd_oldpwd(prev_dir, cmd->envp, exit_code);
	return (*exit_code);
}
