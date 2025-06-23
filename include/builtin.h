/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:03:23 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 18:11:13 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(BUILTIN_H)
# define BUILTIN_H

# include "ast.h"

// echo
int		is_valid_flag_n(const char *arg);
int		execute_builtin_echo(t_ast *ast);
// pwd
int		execute_builtin_pwd(t_ast *ast);
// exit
static int is_numeric(const char *str);
int execute_builtin_exit(t_ast *ast, t_sh *shell);

#endif