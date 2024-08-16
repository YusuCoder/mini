/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ryusupov <ryusupov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:28:22 by ryusupov          #+#    #+#             */
/*   Updated: 2024/08/16 20:41:44 by ryusupov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

volatile sig_atomic_t	g_last_signal_received = 0;
/*Terminal ctrl setting disables echo messages of ctrl signals using flag ECHOCTRL*/
void	_handle_child_signal(int signal)
{
	g_last_signal_received = signal;
	if (signal == SIGINT)
	{
		write(1, "^C\n", 3);
	}
	if (signal == SIGQUIT)
	{
		write(1, "^\\Quit: 3\n", 10);
	}
}

// Signal handler for other signals
void	_handle_other_signals(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// Function to handle signals setup
void	_handle_signals(t_process stats)
{
	struct sigaction	sa;

	if (stats == CHILD_PROCESS)
	{
		sa.sa_handler = &_handle_child_signal;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (sigaction(SIGQUIT, &sa, NULL) < 0)
			return ;
	}
	else
	{
		sa.sa_handler = &_handle_other_signals;
		sigemptyset(&sa.sa_mask);
		sa.sa_flags = 0;
		if (sigaction(SIGINT, &sa, NULL) < 0)
			return ;
		if (signal(SIGQUIT, SIG_IGN) < 0)
			return ;
	}
}

// Function to determine the exit code
void	determine_exit_code(int exit_code)
{
	if (g_last_signal_received == SIGINT)
		exit_code = 130;
	else if (g_last_signal_received == SIGQUIT)
		exit_code = 131;
	else
		exit_code = 0;
}

void	_init_terminal(int exit_code)
{
	struct termios	term;

	if (tcgetattr(0, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, TCSANOW, &term) != 0)
		_err_msg("Error!\n", EXIT_FAILURE);
	_handle_signals(INIT);
	determine_exit_code(exit_code);
}
