/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:33:59 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:52:09 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redir_fd(t_ast *redir, t_sh *shell)
{
	if (redir->type == AST_REDIR_IN)
		return (handle_redir_in(redir, shell));
	if (redir->type == AST_REDIR_OUT)
		return (handle_redir_out(redir, shell));
	if (redir->type == AST_APPEND)
		return (handle_append(redir, shell));
	if (redir->type == AST_HEREDOC)
		return (handle_heredoc(redir, shell));
	perror("Unknown redirection");
	return (-1);
}

t_ast	*get_command_node(t_ast *node)
{
	if (!node)
		return (NULL);
	if (ast_is_command(node))
		return (node);
	return (get_command_node(node->left));
}

int	apply_redirection(t_ast *ast, t_sh *shell)
{
	t_ast		*cmd;
	t_fctx		*ctx;
	int			fd;

	if (!ast || !ast->left)
		return (-1);
	cmd = get_command_node(ast->left); // to do gestire heredoc (apre anche senza comando)
	if (!cmd)
	{
		fprintf(stderr, "❌ Nessun comando trovato per redirection '%s'\n", ast->value);
		return (-1);
	}
	if (!cmd->fd_ctx)
	{
		cmd->fd_ctx = fd_ctx_new();
		if (!cmd->fd_ctx)
			return (perror("malloc fd_ctx_new"), -1);
	}
	ctx = cmd->fd_ctx;
	fd = get_redir_fd(ast, shell);
	if (fd < 0)
		return (-1);
	set_fd_ctx(ctx, fd, ast->type);
	// fprintf(stderr,
	// 	"✅ Redirection '%s' (tipo=%s) applicata a comando '%s': fd_in=%d, fd_out=%d\n",
	// 	ast->value,
	// 	node_type_name(ast->type),
	// 	cmd->argv && cmd->argv[0] ? cmd->argv[0] : "(null)",
	// 	ctx->fd_in,
	// 	ctx->fd_out);
	return (0);
}

int		preprocess_redirections(t_ast *ast, t_sh *shell)
{
	if (!ast)
		return (0);
	if (preprocess_redirections(ast->left, shell) != 0)
		return (-1);
	if (preprocess_redirections(ast->right, shell) != 0)
		return (-1);
	if (ast_is_redirection(ast))
		return (apply_redirection(ast, shell));
	return (0);
}
