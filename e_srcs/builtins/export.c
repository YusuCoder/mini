
#include "../../includes/minishell.h"

// Handle export argument with no value
void	export_arg_no_value(t_command *cmd, int *exit_code, int i)
{
	char	*name;

	name = cmd->tokens[i];
	if (find_env_var(cmd->envp, name) == -1)
	{
		if (export_set_env(&cmd->envp, name, NULL, 0) != 0)
		{
			perror("export");
			*exit_code = 1;
		}
	}
}

// Handle export argument with value
void	export_arg_with_value(t_command *cmd, int *exit_code, int i,
	char *equal_sign)
{
	char	*name;
	char	*value;

	name = my_strndup(cmd->tokens[i], equal_sign - cmd->tokens[i]);
	value = ft_strdup(equal_sign + 1);
	if (name && value)
	{
		if (export_set_env(&cmd->envp, name, value, 1) != 0)
		{
			perror("export");
			*exit_code = 1;
			return (free(name), free(value));
		}
	}
	else
	{
		write(2, "export: invalid argument\n", 25);
		*exit_code = 1;
		return (free(name), free(value));
	}
	free(name);
	free(value);
}

// Handle export command with arguments
void	export_with_args(t_command *cmd, int *exit_code)
{
	int		i;
	char	*equal_sign;

	i = 1;
	while (cmd->tokens[i])
	{
		equal_sign = ft_strchr(cmd->tokens[i], '=');
		if (equal_sign)
			export_arg_with_value(cmd, exit_code, i, equal_sign);
		else
			export_arg_no_value(cmd, exit_code, i);
		if (*exit_code != 0)
			return ;
		i++;
	}
	*exit_code = 0;
}

// Handle export command with no arguments
void	export_no_args(t_command *cmd, int *exit_code)
{
	char	**sorted_env;
	int		i;
	char	*equal_sign;

	sorted_env = export_sort_env(cmd->envp);
	if (!sorted_env)
	{
		perror("malloc");
		*exit_code = 1;
		return ;
	}
	i = 0;
	while (sorted_env[i])
	{
		equal_sign = ft_strchr(sorted_env[i], '=');
		if (equal_sign)
			printf("declare -x %.*s=\"%s\"\n",
				(int)(equal_sign - sorted_env[i]), sorted_env[i],
				equal_sign + 1);
		else
			printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free(sorted_env);
	*exit_code = 0;
}

// Main export command execution function
int	execute_export(t_command *cmd, int *exit_code)
{
	if (cmd->tokens[1] == NULL)
		export_no_args(cmd, exit_code);
	else
		export_with_args(cmd, exit_code);
	return (*exit_code);
}
