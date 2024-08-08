
#include "../../includes/minishell.h"

// Find environment variable by name
int	find_env_var(char **env, const char *name)
{
	int	name_len;
	int	i;

	name_len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& (env[i][name_len] == '=' || env[i][name_len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

// Create new environment variable string
char	*create_env_var(const char *name, const char *value)
{
	char	*new_env_var;
	size_t	name_len;
	size_t	value_len;

	if (value)
	{
		name_len = ft_strlen(name);
		value_len = ft_strlen(value);
		new_env_var = (char *)malloc(name_len + value_len + 2);
		if (!new_env_var)
			return (NULL);
		ft_strlcpy(new_env_var, name, name_len);
		new_env_var[name_len] = '=';
		ft_strlcpy(new_env_var + name_len + 1, value, value_len);
	}
	else
	{
		new_env_var = ft_strdup(name);
	}
	return (new_env_var);
}

// Add new environment variable to the environment
int	add_new_env_var(char ***env, char *new_env_var)
{
	int		env_len;
	char	**new_env;

	env_len = 0;
	while ((*env)[env_len])
		env_len++;
	new_env = my_realloc(*env, (env_len + 1) * sizeof(char *),
		(env_len + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_env_var);
		return (-1);
	}
	new_env[env_len] = new_env_var;
	new_env[env_len + 1] = NULL;
	*env = new_env;
	return (0);
}

// Set environment variable
int	export_set_env(char ***env, const char *name, const char *value,
	int overwrite)
{
	int		i;
	char	*new_env_var;

	i = find_env_var(*env, name);
	new_env_var = create_env_var(name, value);
	if (!new_env_var)
		return (-1);
	if (i != -1)
	{
		if (overwrite)
		{
			free((*env)[i]);
			(*env)[i] = new_env_var;
		}
		else
			free(new_env_var);
		return (0);
	}
	return (add_new_env_var(env, new_env_var));
}
