/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:16 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/28 03:52:47 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include <readline/readline.h>

// $var -> $var value
// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell)
{
	astt_post_ctx(root, should_expand_token, shell);
}

void	should_expand_token(t_ast *node, void *ctx)
{
	t_sh	*shell;

	shell = (t_sh *)ctx;
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
		expand_command_args(node, shell);
	else if (node->value && node->quote != S_QUOTE)
		expand_token_value(node, shell);
}

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell)
{
	t_list	*lines;
	char	*line;
	char	*exp;
	char	*res;

	lines = NULL;
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, delimiter))
			break ;
		if (quote == N_QUOTE)
		{
			exp = expand_token(line, N_QUOTE, shell);
			free(line);
			line = exp;
		}
		ft_lstadd_back(&lines, ft_lstnew(line));
	}
	res = lst_join(lines);
	ft_lstclear(&lines, free);
	return (res);
}
