/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/06/18 13:39:08 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

#include "minishell.h"

// core
int executor(t_ast *ast, int fd_in, t_sh *shell);
int execute_pipeline(t_ast *ast, int fd_in, t_sh *shell);
int execute_command(t_ast *ast, int fd_in, t_sh *shell);
int execute_builtin(t_ast *ast);

// utils
char *search_path(char *cmd, t_sh *shell);
int spawn_command(t_ast *ast, int fd_in, t_sh *shell);
int is_builtin(t_ast *ast);

#endif
