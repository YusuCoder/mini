/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkubanyc <tkubanyc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 18:29:03 by tkubanyc          #+#    #+#             */
/*   Updated: 2024/08/18 18:43:34 by tkubanyc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_heredoc(char *arg)
{
	if (ft_strncmp(arg, "<<", 2) == 0)
		return (1);
	else
		return (0);
}

int	is_redir_input(char *arg)
{
	if (ft_strncmp(arg, "<", 1) == 0)
		return (1);
	else
		return (0);
}

int	is_redir_otput(char *arg)
{
	if (ft_strncmp(arg, ">", 1) == 0)
		return (1);
	else
		return (0);
}

int	is_redir_append(char *arg)
{
	if (ft_strncmp(arg, ">>", 2) == 0)
		return (1);
	else
		return (0);
}

int	is_redirection(char *arg)
{
	if (is_heredoc(arg)
		|| is_redir_input(arg)
		|| is_redir_otput(arg)
		|| is_redir_append(arg))
		return (1);
	else
		return (0);
}