/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:53:46 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/13 14:05:45 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *erase_and_replace(char **token_array, char *str, char *var_value, int index) {
    int newstr_size;
    char *newstr;
    int i = 0, j = 0;

    // Calculate the size of the new string
    newstr_size = strlen(str) - var_length(str + index) + strlen(var_value);

    // Allocate memory for the new string
    newstr = (char *)malloc(sizeof(char) * (newstr_size + 1));
    if (!newstr)
        return NULL;

    // Copy characters from the original string to the new string
    while (str[i]) {
        if (i == index) {
            // Replace the variable with var_value
            strcpy(&newstr[j], var_value);
            j += strlen(var_value);
            i += var_length(str + index);
            if (str[i] == '\0')
                break;
        } else {
            newstr[j++] = str[i++];
        }
    }
    newstr[j] = '\0';

    // Free the old string in the token array and update it with the new string
    free(*token_array);
    *token_array = newstr;

    return newstr;
}

int erase_var(char **token_array, char *str, int index) {
    int i = 0;
    int j = 0;
    int len;
    char *new_str;

    // Calculate the length of the new string after removing the variable
    len = strlen(str) - var_length(str + index);
    new_str = (char *)malloc(sizeof(char) * (len + 1));
    if (!new_str)
        return 1;

    // Copy characters to the new string, skipping the variable
    while (str[i]) {
        if (str[i] == '$' && i == index) {
            i += var_length(str + index) + 1;
            if (str[i] == '\0')
                break;
        } else {
            new_str[j++] = str[i++];
        }
    }
    new_str[j] = '\0';

    // Free the old string and update the pointer
    // free(*token_array);
    *token_array = new_str;
    return 0;
}


int replace_var(char **token_array, char *var_value, int index) {
    char *current_token = token_array[index];

    if (var_value == NULL) {
        if (erase_var(&current_token, current_token, index) == 1) {
            free_ptr(var_value);
            return 1;
        }
    } else {
        if (erase_and_replace(&current_token, current_token, var_value, index) == NULL) {
            free_ptr(var_value);
            return 1;
        }
    }

    free_ptr(var_value);
    token_array[index] = current_token;
    return 0;
}


void update_status(char **current_token, char c, int *status)
{
    if (c == '\'' && *status == DEFAULT)
        *status = SQUOTE;
    else if (c == '\"' && *status == DEFAULT)
        *status = DQUOTE;
    else if (c == '\'' && *status == SQUOTE)
        *status = DEFAULT;
    else if (c == '\"' && *status == DQUOTE)
        *status = DEFAULT;
}

bool	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

bool	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (true);
		else
			return (false);
	}
	return (false);
}

int var_expander(t_command *data, char **token_array)
{
    int i;
    int j;
    int current_status;

    i = 0;
    while(token_array[i] != NULL)
    {
        char *current_token = token_array[i];
        j = 0;

        current_status = DEFAULT;
        while (current_token[j])
        {
            update_status(&current_token, current_token[j], &current_status);
            if (current_token[j] == '"')
            {
                if (current_status == DQUOTE)
                {
                     current_status = DEFAULT;
                } else
                     current_status = DQUOTE;
            }
            if (current_token[j] == '$'
                && !is_next_char_a_sep(current_token[j + 1])
                && !var_between_quotes(current_token, j)
                && (current_status == DEFAULT || current_status == DQUOTE)) {

                replace_var(&current_token, recover_val(data, current_token + j), j);
            } else {
                j++;
            }
        }
        i++;
    }

    return 0;
}

// int var_expander(t_command *data, char **token_array)
// {
//     int i = 0;
//     int j = 0;
//     int current_status = DEFAULT;

//     while (token_array[i] != NULL)
//     {
//         char *current_token = token_array[i];
//         j = 0;
//         current_status = DEFAULT;

//         while (current_token[j])
//         {
//             update_status(&current_token, current_token[j], &current_status);

//             if (current_token[j] == '"')
//             {
//                 if (current_status == DQUOTE)
//                     current_status = DEFAULT;
//                 else
//                     current_status = DQUOTE;
//             }

//             if (current_token[j] == '$'
//                 && !is_next_char_a_sep(current_token[j + 1])
//                 && !var_between_quotes(current_token, j)
//                 && (current_status == DEFAULT || current_status == DQUOTE))
//             {
//                 // Call recover_val with the correct parameters
//                 char *value = recover_val(data, current_token + j);
//                 if (value != NULL)
//                 {
//                     replace_var(&current_token, value, j);
//                 }
//             }
//             else
//             {
//                 j++;
//             }
//         }
//         i++;
//     }
//     return 0;
// }


int main() {
    // Sample data for testing
    t_command data;
    char *env[] = {"USER=testuser", "HOME=/home/testuser", NULL};
    data.envp = env;

    char *tokens[] = {
        strdup("echo $USER"),
        strdup("ls $HOME"),
        strdup("echo \"$PATH\""),
        NULL
    };

    // Call the function to expand variables
    var_expander(&data, tokens);

    // Print the results
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
        free(tokens[i]);  // Clean up allocated memory
    }

    return 0;
}

