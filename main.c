/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:46:35 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/09 14:19:31 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	execute_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}


char	*read_line(char *line)
{
	char *cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (line)
	{
		free(line);
		line = NULL;
	}
	char *slash = ft_strchr(cwd, '/');
	if (slash)
	{
		cwd = slash + 7;
	}
	printf(RED"~/%s $\n"RESET, cwd);
	line = readline(GREEN">>> "RESET);
	if (line && *line != '\0')
		add_history(line);
	return (line);
}

int	main(void)
{
	char	*line;

	line = NULL;
	while(1)
	{
		line = read_line(line);
		if (!line)
			break ;
		if (ft_strcmp(line, "pwd") == 0)
			execute_pwd();
	}
	return (0);
}
