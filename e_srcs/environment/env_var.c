
#include "../../includes/minishell.h"

// Find environment variable by name
int	env_var_find(char **env, const char *name)
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
char	*env_var_create(const char *name, const char *value)
{
	char	*new_env_var;
	char	*temp;

	if (value)
	{
		temp = ft_strjoin(name, "=");
		new_env_var = ft_strjoin(temp, value);
		free(temp);
	}
	else
	{
		new_env_var = ft_strdup(name);
	}
	return (new_env_var);
}

// Add new environment variable to the environment
int	env_var_add(char ***env, char *new_env_var)
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

// Remove variable from environment
int	env_var_remove(char ***env, int index)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	while ((*env)[i])
		i++;
	new_env = (char **)malloc(sizeof(char *) * i);
	if (!new_env)
		return (-1);
	i = -1;
	j = -1;
	while ((*env)[i])
	{
		if (++i != index)
			new_env[++j] = (*env)[i];
		else
			free((*env)[i]);
	}
	new_env[j] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
