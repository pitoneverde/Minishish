/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/05/25 21:48:15 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef TILE
#  define TILE 64
# endif

# include "libft.h"
# include "ast.h"
# include "parser.h"
# include "env.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// ONLY GLOBAL ALLOWED
// NOTE: extern variables count as global defined elsewhere
// must pass context as a struct (also for history)
static volatile sig_atomic_t g_signal_status = 0;

int sum(int a, int b);

// Utils
void	print_error(char *s);

// Signals
void	handler_sigaction(int sig);

#endif