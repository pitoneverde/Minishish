/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/05/22 17:57:41 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef TILE
#  define TILE 64
# endif

# include "libft.h"
# include "matrix_helpers.h"
# include "ast.h"
# include "parser.h"

# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

int sum(int a, int b);

// Utils
void	print_error(char *s);

// Signals
void	handler_sigaction(int sig);

#endif