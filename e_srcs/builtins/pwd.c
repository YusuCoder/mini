/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:18:11 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 21:01:52 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pwd(int *exit_code)
{
	char	curr_dir[1024];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("getcwd");
		*exit_code = 1;
		return (1);
	}
	printf("%s\n", curr_dir);
	*exit_code = 0;
	return (0);
}
