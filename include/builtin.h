/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:03:23 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 16:09:07 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(BUILTIN_H)
# define BUILTIN_H

# include "ast.h"

int is_valid_flag_n(const char *arg);
int	execute_builtin_echo(t_ast *ast);


#endif