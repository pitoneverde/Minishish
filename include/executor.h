/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:07:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/06 18:05:17 by plichota         ###   ########.fr       */
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

// execute redirection
int		execute_redirection_chain(t_ast *ast, t_sh *shell, int fd_in, int fd_out, int is_fork, int is_in_pipeline);

// redirection helpers
int		handle_redir_in(t_ast *node, t_sh *shell);
int		handle_redir_out(t_ast *node, t_sh *shell);
int		handle_append(t_ast *node, t_sh *shell);
int		handle_heredoc(t_ast *node, t_sh *shell);

// execute other
int		execute_builtin(t_ast *ast, int fd_out, t_sh *shell);

// core
int		executor(t_ast *ast, int fd_in, int fd_out, t_sh *shell, int is_fork, int is_in_pipeline);
int		is_builtin(t_ast *ast);
#endif
