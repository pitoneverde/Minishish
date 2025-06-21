/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/06/21 18:36:58 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handler_sigaction(int sig)
{
	(void)sig;

	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void init_signals()
{
	struct sigaction	sa;

	sa.sa_handler = handler_sigaction;
    sa.sa_flags = SA_RESTART; // evita che readline() fallisca con NULL dopo un Ctrl-C;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGINT, &sa, NULL);
	// signal(SIGQUIT, SIG_IGN);
}