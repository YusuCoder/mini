/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_tokenize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:12:25 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/16 18:02:52 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**tokenizing(const char *str)
{
	char	**t;
	int		words;
	int		words1;
	int		x;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	words = count_words(str, i);
	if (words < 1)
		return (NULL);
	t = (char **)malloc(sizeof(t) * (words + 1));
	if (!t)
		return (NULL);
	words1 = 0;
	x = 0;
	if (add_tokens(t, str, words1, x) < 0)
		return (NULL);
	t[words] = NULL;
	return (t);
}
