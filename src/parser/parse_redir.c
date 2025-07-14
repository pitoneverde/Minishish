/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 18:45:21 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/14 18:47:41 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_ast	*pre_check_redir(t_ast *cmd, t_parser *p);

// Helper to parse a single redirection and return the updated command node
t_ast	*parse_redirection(t_parser *p, t_ast *cmd)
{
	char	*op;
	char	*filename;
	t_ast	*f_node;
	t_ast	*r_node;
	t_token	*redir;

	redir = p->current;
	advance(p);
	if (pre_check_redir(cmd, p))
		return (pre_check_redir(cmd, p));
	op = ft_strdup(redir->value);
	filename = ft_strdup(p->current->value);
	f_node = ast_new(AST_LITERAL, filename);
	if (f_node)
		f_node->quote = p->current->quote;
	free(filename);
	advance(p);
	if (!f_node || !tkn_is_redirection(redir))
		return (free(op), ast_free(cmd), ast_free(f_node),
			syntax_error_token(redir->value));
	r_node = ast_binary_op((t_ast_type)redir->type, op, astdup(cmd), f_node);
	if (!r_node)
		return (ast_free(cmd), free(op), ast_free(f_node),
			syntax_error_token(p->current->value));
	return (ast_free(cmd), free(op), r_node);
}

static t_ast	*pre_check_redir(t_ast *cmd, t_parser *p)
{
	if (!p->current)
		return (ast_free(cmd), syntax_error_token("newline"));
	if (!tkn_is_word(p->current))
		return (ast_free(cmd), syntax_error_token(p->current->value));
	return (NULL);
}
