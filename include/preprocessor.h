/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:31:24 by plichota          #+#    #+#             */
/*   Updated: 2025/07/10 23:36:22 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

// redirection helpers
int		handle_redir_in(t_ast *node, t_sh *shell);
int		handle_redir_out(t_ast *node, t_sh *shell);
int		handle_append(t_ast *node, t_sh *shell);

// heredoc
int		heredoc_loop(char *delim, int fd_out);
int		handle_heredoc(t_ast *node, t_sh *shell);

// utils
int		get_redir_fd(t_ast *redir, t_sh *shell);

// fd utils
void	set_std_fd(int fd_in, int fd_out);
void	override_fd_with_ctx(t_ast *ast, int *new_fd_in, int *new_fd_out);

// utils
int		apply_redirection(t_ast *ast, t_sh *shell);
int		preprocess_redirections(t_ast *node, t_sh *shell);
void	close_unused_fds(t_ast *ast, int used_fd_in, int used_fd_out);
