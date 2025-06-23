/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/06/23 18:25:40 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "shell.h"

// core
int		executor(t_ast *ast, int fd_in, t_sh *shell);
int		execute_pipeline(t_ast *ast, int fd_in, t_sh *shell);
int		execute_command(t_ast *ast, int fd_in, t_sh *shell);
int		execute_builtin(t_ast *ast, t_sh *shell);

// utils
int		spawn_command(t_ast *ast, int fd_in, t_sh *shell);
int		is_builtin(t_ast *ast);
char	*search_path(char *cmd, t_sh *shell);
char	*find_command_path(char *cmd, char **paths);

#endif
