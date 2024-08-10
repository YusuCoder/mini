
#include "./includes/minishell.h"

char	*read_line(char *line)
{
	char	*cwd;
	char	*home;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (line)
	{
		free(line);
		line = NULL;
	}
	home = getenv("HOME");
	if (home && ft_strncmp(cwd, home, ft_strlen(home)) == 0)
	{
		cwd += ft_strlen(home);
		if (*cwd == '/')
			cwd++;
	}
	printf(RED"~/%s $\n"RESET, cwd);
	line = readline(GREEN">>> "RESET);
	if (line && *line != '\0')
		add_history(line);
	return (line);
}

// void print_envp(char **envp) {
//     int i = 0;
//     while (envp[i] != NULL) {
//         printf("%s\n", envp[i]);
//         i++;
//     }
// }

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_command	t;
	int			exit_code;

	(void)argv;
	(void)argc;
	line = NULL;
	exit_code = 0;
	_init_terminal(&gl_command, envp);
	t.envp = env_set(envp);
	env_value_delete(t.envp, "OLDPWD");
	// print_envp(t.envp);
	while(1)
	{
		line = read_line(line);
		if (!line)
			break ;
		t.tokens = tokenizing(line);
		int i = 0;
		while (t.tokens && t.tokens[i] != NULL)
		{
			// printf("[ %s ]\n", t.tokens[i]);
			if (parse(t.tokens) && t.tokens)
			{
			}
			i++;

		}
		execute(&t, &exit_code);
		// if (!t.tokens)
		// 	return (0);
	}
	return (exit_code);
}
