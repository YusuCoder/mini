/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:17:14 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/07/29 20:21:34 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_env(char **env, int *exit_code)
{
	int	i;

	i = 0;
	while ((env)[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	*exit_code = 0;
	return (0);
}
