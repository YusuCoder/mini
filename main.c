/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:46:35 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/29 15:30:36 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_command	t;

	line = NULL;
	(void)argv;
	(void)argc;
	_init_terminal(&gl_command, envp);
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
		execute(&t);
		// if (!t.tokens)
		// 	return (0);
		// if (ft_strcmp(line, "pwd") == 0)
		// 	execute_pwd();
	}
	return (0);
}
