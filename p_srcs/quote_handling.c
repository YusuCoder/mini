/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 16:41:07 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/18 22:31:48 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// char	*remove_outer_quotes(char **token)
// {
// 	int		i;
// 	int		j;
// 	char	*new_token;
//     char    *quote_type;

// 	i = 0;
// 	j = 0;
// 	new_token = (char *)malloc(ft_strlen(token) * sizeof(char) + 1);
// 	if (!new_token)
// 		return (NULL);
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '\"')
// 		{
//             quote_type = token[i];
// 			i++;
// 			continue;
// 		}
// 		new_token[j] = token[i];
// 		i++;
// 		j++;
// 	}
// 	new_token[j] = '\0';
// 	return (new_token);
// }

char *remove_first_quote(char *token) {
    int i = 0;
    int j = 0;
    int found_quote = 0;
    int len = ft_strlen(token);
    char *new_token = (char *)malloc((len + 1) * sizeof(char));

    if (!new_token)
        return NULL;

    while (token[i]) {
        if (!found_quote && (token[i] == '\"' || token[i] == '\'')) {
            found_quote = 1;
            i++;
            continue; // Skip the first quote
        }
        new_token[j++] = token[i++];
    }
    new_token[j] = '\0';
    return new_token;
}

char *remove_last_quote(const char *token) {
    int i = ft_strlen(token) - 1;
    int j;
    int found_quote = 0;
    char *new_token;

    while (i >= 0) {
        if (!found_quote && (token[i] == '\"' || token[i] == '\'')) {
            found_quote = 1;
            break;
        }
        i--;
    }
    new_token = (char *)malloc((i + 1) * sizeof(char));
    if (!new_token)
        return NULL;
    j = 0;
    while (j < i) {
        new_token[j] = token[j];
        j++;
    }
    new_token[j] = '\0';
    return new_token;
}

void quote_handing(char **tokens) {
    int i = 0;
    char *temp;

    while (tokens[i]) {
        if (ft_strchr(tokens[i], '\"') || ft_strchr(tokens[i], '\'')) {
            temp = tokens[i];
            // printf("original token: %s\n", tokens[i]);
            tokens[i] = remove_first_quote(tokens[i]);
            // printf("after removing firest quote %s\n", tokens[i]);
            free(temp);
            temp = tokens[i];
            tokens[i] = remove_last_quote(tokens[i]);
            // printf("after removing last quote %s\n", tokens[i]);
            free(temp);
        }
        i++;
    }
}

