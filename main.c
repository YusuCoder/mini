/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:46:35 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/08 19:12:01 by ryusupov         ###   ########.fr       */
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
	if (line)
	{
		free(line);
		line = NULL;
	}
	line = readline("minishell> ");
	if (line && *line)
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
