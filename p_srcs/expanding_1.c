/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rustam <rustam@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-08-12 20:45:45 by rustam            #+#    #+#             */
/*   Updated: 2024-08-12 20:45:45 by rustam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_expand_exception(char c)
{
	if (c == '/' || c == '=' || c == '\"' || c == '$'
		|| c == '\\' || c == '\'' || c == '+' || c == '-')
		return (1);
	return (0);
}

int	is_exit_code(char *token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i + 1] && token[i] == '$' && token[i + 1] == '?')
			return (1);
		i++;
	}
	return (0);
}

int	dollar_remaining(char	*token)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (token[i])
	{
		if (token[i] == '$')
			check += is_not_between_squotes(token, i);
		i++;
	}
	if (check > 0)
		return (1);
	else
		return (0);
}

int	find_first_expansion(char	*token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && is_not_between_squotes(token, i))
			return (i);
		i++;
	}
	return (-1);
}

int	count_poststring(char	*token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if (token[i] == '$' && !cst(token[i])
			&& is_not_between_squotes(token, i))
			break ;
		i++;
	}
	return (i);
}
