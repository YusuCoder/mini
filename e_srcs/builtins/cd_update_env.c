
#include "../../includes/minishell.h"

void	update_env_var(char **env, const char *key, const char *value)
{
	int		i;
	size_t	key_len;
	char	*new_entry;

	i = 0;
	key_len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, key_len) == 0)
		{
			free(env[i]);
			new_entry = ft_strjoin(key, "=");
			env[i] = ft_strjoin(new_entry, value);
			free(new_entry);
			return ;
		}
		i++;
	}
}

void	update_pwd_oldpwd(char *prev_dir, char **env, int *exit_code)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return ;
	}
	update_env_var(env, "OLDPWD", prev_dir);
	update_env_var(env, "PWD", curr_dir);
}
