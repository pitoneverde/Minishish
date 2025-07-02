/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/02 21:11:29 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "shell.h"

// execute command
int		check_command_access(char *path);
int		execute_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell);
char	*search_path(char *cmd, t_sh *shell);
int		spawn_command(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_in_pipeline);
char	*find_command_path(char *cmd, char **paths);

// execute pipeline
int		execute_pipeline(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork);

// execute other
int		execute_builtin(t_ast *ast, t_sh *shell);

// core
int		executor(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork, int is_in_pipeline);
int		is_builtin(t_ast *ast);

#endif
