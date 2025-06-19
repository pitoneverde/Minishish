/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/06/18 13:42:54 by plichota         ###   ########.fr       */
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
# include "executor.h"
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

typedef struct s_sh
{
	t_list	*env;				// list of t_env
	int		last_code;			// for $?
	int		is_interactive;		// set if running interactively
}	t_sh;

int sum(int a, int b);

// Parse line
t_ast	*read_command_line(const char *line);

// Utils
void	print_error(char *s);

// Signals
void	handler_sigaction(int sig);

#endif