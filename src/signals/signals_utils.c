/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 18:28:31 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 14:55:00 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_newline(int sig)
{
	(void) sig;
	write(STDERR_FILENO, "\n", 1);
}

void	update_signal_status(t_sh *shell)
{
	if (!shell)
		return ;
	if (g_last_signal != 0)
	{
		if (g_last_signal == SIGINT)
			shell->last_code = EXIT_SIGINT;
		if (g_last_signal == SIGQUIT)
			shell->last_code = EXIT_SIGQUIT;
		g_last_signal = 0;
	}
}
