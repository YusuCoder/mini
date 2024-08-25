/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:30:26 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/25 22:04:18 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_leading_quotes(char *token)
{
	int	count;

	count = 0;
	while (token[count] && token[count] == '\'')
	{
		count++;
	}
	return (count);
}

int	count_trailing_quotes(char *token)
{
	int	count;
	int	len;

	count = 0;
	len = strlen(token);
	while (len > 0 && token[len - 1] == '\'')
	{
		count++;
		len--;
	}
	return (count);
}

int	are_quotes_even(int left_quotes, int right_quotes)
{
	return ((left_quotes % 2 == 0) && (right_quotes % 2 == 0));
}

void	count_and_find_quotes(char *token, int *start, int *end)
{
	int	left_quotes;
	int	right_quotes;
	int	len;

	left_quotes = count_leading_quotes(token);
	right_quotes = count_trailing_quotes(token);
	len = strlen(token);
	if (are_quotes_even(left_quotes, right_quotes))
	{
		*start = left_quotes;
		*end = len - right_quotes;
	}
	else
	{
		*start = 0;
		*end = len;
	}
}

char	*create_new_token(char *token, int start, int end)
{
	char	*new_token;
	int		j;

	j = 0;
	new_token = (char *)malloc(end - start + 1);
	if (!new_token)
		return (NULL);
	while (start < end)
		new_token[j++] = token[start++];
	new_token[j] = '\0';
	return (new_token);
}