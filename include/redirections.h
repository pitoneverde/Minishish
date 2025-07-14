/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:31:24 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:43:07 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H

# include "ast.h"

// redirection helpers
int		handle_redir_in(t_ast *node, t_sh *shell);
int		handle_redir_out(t_ast *node, t_sh *shell);
int		handle_append(t_ast *node, t_sh *shell);

// heredoc
void	restore_state(int saved_stdin);
char	*expand_variables(char *line, t_sh *shell);
int		heredoc_loop(char *delim, int fd_out, t_sh *shell);
int		handle_heredoc(t_ast *node, t_sh *shell);

// utils
int		get_redir_fd(t_ast *redir, t_sh *shell);

// fd utils
void	set_std_fd(int fd_in, int fd_out);
void	override_fd_with_ctx(t_ast *ast, int *new_fd_in, int *new_fd_out);

// utils
int		apply_redirection(t_ast *ast, t_sh *shell);
int		process_ast_redirections(t_ast *node, t_sh *shell);
void	close_unused_fds(t_ast *ast, int used_fd_in, int used_fd_out);

#endif