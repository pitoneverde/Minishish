/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:12:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:48:32 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SIGNALS_H)
# define SIGNALS_H

# include "ast.h"
# include <signal.h>

# define EXIT_HEREDOC_SIGINT	-2
# define EXIT_SIGINT			130		/* Ctrl-C */
# define EXIT_SIGQUIT			131		/* Ctrl-\ */
// # define EXIT_SIGTERM		143		/* kill */
// # define EXIT_SIGPIPE		141		/* write on pipe with no reader */
// # define EXIT_SIGSTP			146		/* Ctrl-Z End of Transmission*/

/*
	Ctrl-D NON e' un segnale:
	manda il carattere EOT (ascii 0x04) al driver TTY
	che lo interpreta come "nessun altro byte da leggere".
	-	Se il buffer della linea e' vuoto:
		chiude la linea per cui read() restituisce 0 e
		l'applicazione vede EOF
	-	Se il buffer contiene caratteri:
		consegna quei byte al processo (scartando EOT).
		L'EOF arriva alla read successiva solo se non si
		digita altri caratteri
*/

extern volatile sig_atomic_t	g_last_signal;

// core
void	init_signals(void);
void	init_heredoc_signals(void);
void	set_default_signals(void);
void	ignore_signals(void);

// handlers
void	handler_sigaction(int sig);
void	handler_sigint_heredoc(int sig);

// utils
void	print_newline(int sig);
void	update_signal_status(t_sh *shell);

#endif