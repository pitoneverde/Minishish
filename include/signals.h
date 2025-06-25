/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:12:47 by plichota          #+#    #+#             */
/*   Updated: 2025/06/25 16:25:04 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(SIGNALS_H)
# define SIGNALS_H

# include <signal.h>

extern volatile sig_atomic_t g_signal_status;

void	init_signals(void);
void	handler_sigaction(int sig);

#endif