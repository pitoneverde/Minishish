/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/05/19 19:35:46 by plichota         ###   ########.fr       */
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
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

int sum(int a, int b);

// Utils
void	print_error(char *s);
#endif