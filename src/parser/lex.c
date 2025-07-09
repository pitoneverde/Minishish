/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:12:12 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 16:56:18 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*init_token(t_list *raw_tokens);

// early returns are all malloc-related
t_list	*lex(t_list *raw_tokens)
{
	t_list	*lexemes;
	t_token	*token;
	t_list	*new_node;

	lexemes = NULL;
	while (raw_tokens)
	{
		token = init_token(raw_tokens);
		if (!token)
			return (free_token_list(&lexemes), NULL);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (free_token(token), free_token_list(&lexemes), NULL);
		ft_lstadd_back(&lexemes, new_node);
		raw_tokens = raw_tokens->next;
	}
	return (lexemes);
}

static t_token	*init_token(t_list *raw_tokens)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->error = NULL;
	token->value = ft_strdup((char *)raw_tokens->content);
	if (!token->value)
		return (free(token), NULL);
	token->type = classify_token(token->value);
	token->quote = classify_quote(token->value);
	if (!strip_if_quoted(token))
		return (free_token(token), NULL);
	check_for_errors(token);
	return (token);
}

// 1 if stripped, 0 otherwise
int	strip_if_quoted(t_token *token)
{
	char	*stripped;

	if ((token->quote == S_QUOTE || token->quote == D_QUOTE)
		&& ft_strlen(token->value) >= 2)
	{
		stripped = ft_substr(token->value, 1, ft_strlen(token->value) - 2);
		free(token->value);
		token->value = stripped;
		if (!token->value)
			return (0);
	}
	return (1);
}
