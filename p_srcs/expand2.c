/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:06:48 by rustam            #+#    #+#             */
/*   Updated: 2024/08/13 14:11:35 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_var_compliant(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

// int	var_length(char *str)
// {
// 	int		i;
// 	int		count;

// 	count = 0;
// 	i = 0;
// 	while (str[i] != '$')
// 		i++;
// 	i++;
// 	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
// 		return (count + 1);
// 	while (str[i])
// 	{
// 		if (is_var_compliant(str[i]) == false)
// 			break ;
// 		count++;
// 		i++;
// 	}
// 	return (count);
// }

int var_length(char *str) {
    int i = 0;
    int count = 0;

    // Find the first occurrence of '$'
    while (str[i] && str[i] != '$') i++;

    // If the string ends before finding '$', return 0
    if (!str[i]) return 0;

    // Move past the '$'
    i++;

    // Special case for single-character variables
    if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?') {
        return 1;
    }

    // Count compliant characters
    while (str[i] && is_var_compliant(str[i])) {
        count++;
        i++;
    }

    return count;
}

char	*identify_var(char *str)
{
	char	*var;
	char	*tmp;
	int		start;
	int		len;
	int		i;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = var_length(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	var = tmp;
	return (var);
}

int var_exists(char **env, char *var)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(var);
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            return 0; // Variable exists
        i++;
    }
    return 1; // Variable does not exist
}

char *search_env_var(char **env, char *var)
{
    char *str;
    int i;
    int len;

    i = 0;
    len = ft_strlen(var);
    while (env[i])
    {
        if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
            break;
        i++;
    }
    if (env[i])
        str = ft_strdup(env[i] + len + 1); // Skip '='
    else
        str = NULL;
    return str;
}

char *recover_val(t_command *data, char *str)
{
    char *value;
    char *var;

    var = identify_var(str);
    if (var != NULL && var_exists(data->envp, var) == 0)
    {
        value = search_env_var(data->envp, var);
    }
    // else if (var && var[0] == '?' && var[1] == '=')
    // {
    //     value = ft_itoa(g_last_exit_code);
    // }
    else
    {
        value = NULL;
    }

    free(var); // Free the variable name
    return value;
}



// char *recover_val(char **env, char *str)
// {
//     char *value;
//     char *var;

//     var = identify_var(str); // Assuming this function extracts the variable name
//     if (var)
//     {
//         if (var_exists(env, var) == 0)
//         {
//             value = search_env_var(env, var);
//         }
//         // else if (var[0] == '?' && var[1] == '=')
//         // {
//         //     value = ft_itoa(g_last_exit_code); // Convert exit code to string
//         // }
//         else
//         {
//             value = NULL;
//         }
//         free(var); // Free the allocated memory for variable name
//     }
//     else
//     {
//         value = NULL;
//     }
//     return value;
// }
