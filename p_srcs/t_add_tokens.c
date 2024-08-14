/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_add_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:54:19 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/14 20:29:16 by ryusupov         ###   ########.fr       */
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
static int	copy_tokens(char *where, const char *from, int	len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		where[i] = from[i];
		i++;
	}
	where[i] = '\0';
	return (len);

}
/*allocating the memory to keep the array of the tokens*/
static int	alloc_tokens (char **token, int counter, int len)
{
	token[counter] = (char *)malloc(sizeof(char) * (len + 1));
	if (!token[counter])
		_err_msg("Allocation failed!\n", EXIT_FAILURE);
	return (0);
}
/*
It iterates through each character of the input string str.
If the character is a word it increments the index i and continues to the next character.
Otherwise, it calculates the length of the token starting from the current index i.
If the token has a single character it adds the length of the word plus one for '/0'.
Otherwise, it iterates through the characters until it finds the end of the token.
Then allocating the memory for the tokens.
at the end copying the token to the allocated memory
*/

int take_tokens(char **token, const char *str, int counter, int i)
{
    int len;
    int res;

    while (str[i])
    {
        if (count_str(str[i]))
            i++;
        else
        {
            len = 0;
            if (count_tokens(str[i]) == 1)
                len = 1; // Single character tokens
            else if (count_tokens(str[i]) == 2)
                len = matching_quotes(str + i); // Handle quoted strings
            else
            {
                while (str[i + len] && !count_str(str[i + len]) && count_tokens(str[i + len]) != 1)
                {
                    len++;
                }
            }
            res = alloc_tokens(token, counter, len);
            i += copy_tokens(token[counter++], str + i, len);
        }
    }
    return res;
}
// int	take_tokens(char **token, const char *str, int counter, int i)
// {
// 	int	len;
// 	int	res;

// 	while (str[i])
// 	{
// 		if (count_str(str[i]))
// 			i++;
// 		else
// 		{
// 			len = 0;
// 			if (count_tokens(str[i]) == 1)
// 				len += get_word_len(str, i) + 1;
// 			else
// 			{
// 				while (!count_str(str[i + len]) && count_tokens(str[i + len]) != 1 && str[i + len])
// 				{
// 					len += matching_quotes(str + i) + 1;
// 					len += check_for_additional_token(str + i + len);
// 				}
// 			}
// 			res = alloc_tokens(token, counter, len);
// 			i += copy_tokens(token[counter++], str + i, len);
// 		}
// 	}
// 	return (res);
// }
