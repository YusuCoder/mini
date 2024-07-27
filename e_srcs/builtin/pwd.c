/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 13:18:11 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/27 13:20:40 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_pwd(void)
{
	char	*cwd;

	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (0);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
