/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/07/12 21:56:30 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handle Ctrl-C in heredoc (exit heredoc)
// close STDIN for breaking the while loop of heredoc
void	handler_sigint_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		g_last_signal = SIGINT;
		close(STDIN_FILENO);
	}
}

// handle Ctrl-C (break line)
void	handler_sigaction(int sig)
{
	if (sig == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_last_signal = SIGINT;
	}
}
