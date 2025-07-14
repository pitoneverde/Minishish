/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:36:31 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "ast.h"
# include "shell.h"
# include "process.h"

// execute command
int		execute_command(t_ast *ast, t_sh *shell);
void	handle_child(t_ast *ast, t_sh *shell);
int		spawn_command(t_ast *ast, t_sh *shell);

// execute command utils
int		check_command_access(char *path);
char	*search_path(char *cmd, t_sh *shell);
char	*find_command_path(char *cmd, char **paths);
void	init_process_data(t_ast *ast, t_sh *shell);

// execute pipeline
void	handle_pipe_child(int *fd, t_ast *ast, t_sh *shell);
int		handle_pipe_parent(int *fd, pid_t left_pid, t_sh *shell, t_ast *ast);
int		execute_pipeline(t_ast *ast, t_sh *shell);

// execute operator
// int		execute_operator(t_ast *ast, t_sh *shell);

// execute builtin
int		execute_builtin(t_ast *ast, t_sh *shell);

// core
int		dispatch_command(t_ast *ast, t_sh *shell);
int		executor(t_ast *ast, t_sh *shell);
int		is_builtin(t_ast *ast);

#endif
