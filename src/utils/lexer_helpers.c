/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:09:50 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 17:06:25 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// 1 if errors, 0 otherwise
int check_for_errors(t_token *token)
{
	const char *error_prefix;

	if (token->type != TKN_ERROR)
		return (0);
	if (token->value[0] == '\'')
		error_prefix = "Unclosed single quote: ";
	else if (token->value[0] == '"')
		error_prefix = "Unclosed double quote: ";
	else
		error_prefix = "Unknown token: ";
	token->error = ft_strjoin(error_prefix, token->value);
	return (token->error != NULL);
}

void free_token(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	if (token->value)
		free(token->value);
	if (token->error)
		free(token->error);
	if (token)
		free(token);
}

void free_token_list(t_list **list)
{
	ft_lstclear(list, free_token);
}

int tkn_is_redirection(t_token *token)
{
	return (token->type == TKN_REDIR_IN ||
			token->type == TKN_REDIR_OUT ||
			token->type == TKN_APPEND ||
			token->type == TKN_HEREDOC);
}

int tkn_is_word(t_token *token)
{
	return (token->type == TKN_WORD || token->type == TKN_ERROR);
}