/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 18:20:40 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "shell.h"
# include "libft.h"
# include "ast.h"
# include "parser.h"
# include "expansion.h"
# include "signals.h"
# include "executor.h"
# include "builtin.h"

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// ONLY GLOBAL ALLOWED
// NOTE: extern variables count as global defined elsewhere
// must pass context as a struct (also for history)
static volatile sig_atomic_t	g_signal_status = 0;

// Parse line
t_ast	*read_command_line(const char *line);

// Utils
void	free_all(t_sh *shell);
int		is_numeric(const char *str);

void	print_string_matrix(char **matrix);
void	*copy_string(void *str);

#endif