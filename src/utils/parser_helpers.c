/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:06:53 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/10 16:00:22 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "strings.h"

t_ast	*unwrap_command(t_ast *node)
{
	while (ast_is_redirection_chain(node))
		node = node->left;
	if (ast_is_command(node))
		return (node);
	return (NULL);
}

t_ast	*syntax_error_token(char *token_value)
{
	t_sb	*sb;
	t_ast	*err;
	char	*msg;

	sb = sb_create(32);
	if (!sb)
	{
		err = ast_error("syntax error");
		if (!err)
			return (NULL);
		return (err);
	}
	sb_append_str(sb, "syntax error near unexpected token `");
	sb_append_str(sb, token_value);
	sb_append_char(sb, '`');
	msg = sb_build(sb);
	err = ast_error(msg);
	printf("%s\n", err->error);
	free(msg);
	sb_free(sb);
	if (!err)
		return (NULL);
	return (err);
}