/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_add_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:19 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/19 21:49:50 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*this funciton checks if there is any additional character after
the given token. And returns the index of the first cahracter after the token*/
// static int	check_for_additional_token(const char *token)
// {
// 	int	i;

// 	i = 0;
// 	while (token[i] && count_tokens(token[i]) != 1 && !count_str(token[i]))
// 	{
// 		i++;
// 	}
// 	return (i);
// }
/*this function copies the the tokens from input to allocated memory*/
// static int	copy_tokens(char *where, const char *from, int	len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		where[i] = from[i];
// 		i++;
// 	}
// 	where[i] = '\0';
// 	return (len);

// }
/*allocating the memory to keep the array of the tokens*/
int	alloc_tokens(char **token, int counter, int len)
{
	token[counter] = (char *)malloc((len + 1) * sizeof(char));
	if (!token[counter])
	{
		fprintf(stderr, "Memory allocation failed for token[%d]\n", counter);
		exit(EXIT_FAILURE);
	}
	return (0);
}
/*
It iterates through each character of the input string str.
If the character is a word it increments the index i and continues to the next character.
Otherwise,
	it calculates the length of the token starting from the current index i.
If the token has a single character it adds the length of the word plus one for '/0'.
Otherwise,
	it iterates through the characters until it finds the end of the token.
Then allocating the memory for the tokens.
at the end copying the token to the allocated memory
*/
int	handle_variable_or_quoted_string(const char *str)
{
	char	quote;
	int		len;

	len = 1;
	if (str[len] == '"' || str[len] == '\'')
	{
		quote = str[len];
		len++;
		while (str[len] && str[len] != quote)
		{
			len++;
		}
		if (str[len] == quote)
			len++;
	}
	else
	{
		while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
			len++;
	}
	return (len);
}
// int	take_tokens(char **token, const char *str, int i)
// {
// 	int		counter;
// 	// int		in_quotes;
// 	char	quote_char;

// 	counter = 0;
// 	int j, len;
// 	while (str[i])
// 	{
// 		while (str[i] == ' ' || str[i] == '\t')
// 			i++;
// 		if (str[i] == '\0')
// 			break ;
// 		len = 0;
// 		// in_quotes = 0;
// 		quote_char = '\0';
// 		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
// 		{
// 			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
// 					+ 1] == '<'))
// 				len = 2;
// 			else
// 				len = 1;
// 		}
// 		else
// 		{
// 			if (str[i] == '\'' || str[i] == '\"')
// 			{
// 				// in_quotes = 1;
// 				quote_char = str[i];
// 				len++;
// 				while (str[i + len])
// 				{
// 					len++;
// 					if (str[i + len - 1] == quote_char)
// 						break ;
// 				}
// 			}
// 			else
// 			{
// 				while (str[i + len] && (str[i + len] != ' ' && str[i
// 						+ len] != '\t' && str[i + len] != '|' && str[i
// 						+ len] != '>' && str[i + len] != '<' && str[i
// 						+ len] != '\'' && str[i + len] != '\"'))
// 					len++;
// 			}
// 		}
// 		token[counter] = (char *)malloc((len + 1) * sizeof(char));
// 		if (!token[counter])
// 		{
// 			for (j = 0; j < counter; j++)
// 				free(token[j]);
// 			return (-1);
// 		}
// 		strncpy(token[counter], &str[i], len);
// 		token[counter][len] = '\0';
// 		counter++;
// 		i += len;
// 	}
// 	return (counter);
// }

int	take_tokens(char **token, const char *str, int i)
{
	int		counter;
	int		j;
	int		len;
	int		in_quotes;
	char	quote_char;

	counter = 0;
	while (str[i])
	{
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (str[i] == '\0')
			break ;
		len = 0;
		in_quotes = 0;
		quote_char = '\0';
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
		{
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' && str[i
					+ 1] == '<'))
				len = 2;
			else
				len = 1;
		}
		else
		{
			while (str[i + len] && (in_quotes || (str[i + len] != ' ' && str[i
						+ len] != '\t' && str[i + len] != '|' && str[i
						+ len] != '>' && str[i + len] != '<')))
			{
				if ((str[i + len] == '\'' || str[i + len] == '\"')
						&& !in_quotes)
				{
					in_quotes = 1;
					quote_char = str[i + len];
				}
				else if (str[i + len] == quote_char && in_quotes)
					in_quotes = 0;
				len++;
			}
		}
		token[counter] = (char *)malloc((len + 1) * sizeof(char));
		if (!token[counter])
		{
			j = 0;
			while (j < counter)
			{
				free(token[j]);
				j++;
			}
			return (-1);
		}
		ft_memcpy(token[counter], &str[i], len);
		token[counter][len] = '\0';
		counter++;
		i += len;
	}
	return (counter);
}
