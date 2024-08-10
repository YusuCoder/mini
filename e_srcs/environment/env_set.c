
#include "../../includes/minishell.h"

int	env_len(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	**env_set(char **env)
{
	char	**new_env;
	int		len_env;
	int		i;

	len_env = env_len(env);
	new_env = (char **)malloc((len_env + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < len_env)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
