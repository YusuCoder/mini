/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 20:17:20 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/17 20:47:47 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*replace_question(const char *var, int *exit_code)
{
	int		i;
	int		j;
	char	*exit_code_str;
	char	*result;

	i = 0;
	j = 0;
	exit_code_str = ft_itoa(*exit_code);
	while (var[i])
	{
		if (var[i] == '?')
			j += ft_strlen(exit_code_str);
		else
			j++;
		i++;
	}
	result = (char *)malloc((j + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i] == '?')
		{
			strcpy(&result[j], exit_code_str);
			j += ft_strlen(exit_code_str);
		}
		else
			result[j++] = var[i];
		i++;
	}
	result[j] = '\0';
	free(exit_code_str);
	return (result);
}
