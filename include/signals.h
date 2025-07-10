/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:12:47 by plichota          #+#    #+#             */
/*   Updated: 2025/07/10 22:50:33 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SIGNALS_H)
# define SIGNALS_H

# include <signal.h>

# define EXIT_SIGINT	130		/* Ctrl-C */
# define EXIT_SIGQUIT	131		/* Ctrl-\ */
# define EXIT_SIGTERM	143		/* kill */
# define EXIT_SIGPIPE	141		/* scrivere su pipe con lettura chiusa */
# define EXIT_SIGSTP	146		/* Ctrl-Z End of Transmission*/

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

extern volatile sig_atomic_t	g_signal_status;

void	init_signals(void);
void	handler_sigaction(int sig);

// heredoc
void	handler_sigint_heredoc(int sig);

#endif