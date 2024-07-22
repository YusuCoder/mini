/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 16:27:31 by ryusupov          #+#    #+#             */
/*   Updated: 2024/07/22 18:31:48 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	this function checks if the begining of the given arguments is not this tokens if it is the function returns an error
*/
int	check_beginning_and_end(char **t, int i)
{
	if (ft_strncmp(t[i], ">", 1) == 0 || ft_strncmp(t[i], "<", 1) == 0)
		_err_msg("Error! Parsing!\n", EXIT_FAILURE);
	if (t[i] && (ft_strncmp(t[0], "|", 1) == 0 || (i >= 1 && ft_strncmp(t[i], "|", 1) == 0)))
		_err_msg("Error! Parsing!\n", EXIT_FAILURE);
	return (0);
}
/*
	here im cheching for the tokens if the are correctly given
	e.g: cat < | wc -l OR echo helloWorld > > log.txt
*/
int	parse_redirs(char *current, char *next)
{
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "|", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, "<", 1) == 0) && (ft_strncmp(next, ">", 1) == 0))
		return (-1);
	if ((ft_strncmp(current, ">", 1) == 0) && (ft_strncmp(next, "<", 1) == 0))
		return (-1);
	return (0);
}
/*
	This function counts number of single or double quotes
	if number of any of them is odd that means that quote is not closed
*/
int	quotes_check(char *t)
{
	int	i = 0;
	int	s_quote = 0;
	int	d_quote = 0;
	while (t[i])
	{
		if (t[i] == '\'')
			s_quote++;
		if (t[i] == '\"')
			d_quote++;
		i++;
	}
	if (s_quote % 2 != 0 || d_quote % 2 != 0)
		return (-1);
	return (0);
}

int	parse(char	**t)
{
	int	i = 0;

	if (t[i] == NULL)
		return (0);
	while (t[i])
	{
		if (quotes_check(t[i]) < 0)
			_err_msg("Error!\n", EXIT_FAILURE);
		if (t[i + 1] && (((ft_strncmp(t[i], "|", 1) == 0) && (ft_strncmp(t[i + 1], "|", 1) == 0)) || parse_redirs(t[i], t[i + 1]) < 0))
		{
			_err_msg("Error!\n", EXIT_FAILURE);
		}
		i++;
	}
	if (ft_strncmp(t[i - 1], ">", 1) == 0 || ft_strncmp(t[i - 1], "<", 1) == 0)
		_err_msg("Error! Parsing!\n", EXIT_FAILURE);
	if (t[i - 1] && (ft_strncmp(t[0], "|", 1) == 0 || (i - 1 >= 1 && ft_strncmp(t[i - 1], "|", 1) == 0)))
		_err_msg("Error! Parsing!\n", EXIT_FAILURE);
	return (1);
}

// int main() {
//     char *test1[] = {"echo", "hello", "world", NULL};
//     char *test2[] = {"echo", "\"hello world\"", ">", "output.txt", NULL};
//     char *test3[] = {"cat", "<", "input.txt", "|", "grep", "search_term", NULL};
//     char *test4[] = {"|", "echo", "error", NULL}; // Invalid test case
//     char *test5[] = {"echo", "unmatched", "\"", NULL}; // Invalid test case
//     char *test6[] = {"echo", "multiple", ">", ">", "error", NULL}; // Invalid test case

//     if (parse(test1) == 0)
//         printf("Test 1 passed.\n");
//     else
//         printf("Test 1 failed.\n");

//     if (parse(test2) == 0)
//         printf("Test 2 passed.\n");
//     else
//         printf("Test 2 failed.\n");

//     if (parse(test3) == 0)
//         printf("Test 3 passed.\n");
//     else
//         printf("Test 3 failed.\n");

//     if (parse(test4) != 0)
//         printf("Test 4 passed.\n");
//     else
//         printf("Test 4 failed.\n");

//     if (parse(test5) != 0)
//         printf("Test 5 passed.\n");
//     else
//         printf("Test 5 failed.\n");

//     if (parse(test6) != 0)
//         printf("Test 6 passed.\n");
//     else
//         printf("Test 6 failed.\n");

//     return 0;
// }
