#include "minishell.h"

// early returns are all malloc-related
t_list *lex(t_list *raw_tokens)
{
	t_list	*lexemes;
	t_token	*token;
	t_list	*new_node;

	lexemes = NULL;
	while (raw_tokens)
	{
		token = malloc(sizeof(t_token));
		if (!token)
			return (free_token_list(&lexemes), NULL);

		token->error = NULL;
		token->value = ft_strdup((char *)raw_tokens->content);
		if (!token->value)
			return (free(token), free_token_list(&lexemes), NULL);

		token->type = classify_token(token->value);
		if (!strip_if_quoted(token))
			return (free_token(token), free_token_list(&lexemes), NULL);
		check_for_errors(token);
		new_node = ft_lstnew(token);
		if (!new_node)
			return (free_token(token), free_token_list(&lexemes), NULL);
		ft_lstadd_back(&lexemes, new_node);
		raw_tokens = raw_tokens->next;
	}
	return lexemes;
}

// 1 if stripped, 0 otherwise
int strip_if_quoted(t_token *token)
{
	char	*stripped;

	if ((token->type == TKN_S_QUOTED || token->type == TKN_D_QUOTED) &&
		ft_strlen(token->value) >= 2)
	{
		stripped = ft_substr(token->value, 1, ft_strlen(token->value) - 2); // 1 for quote 1 for null
		free(token->value);
		token->value = stripped;
		if (!token->value)
			return (0);
	}
	return (1);
}

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
		error_prefix = "Unknown token error: ";
	token->error = ft_strjoin(error_prefix, token->value);
	return (token->error != NULL);
}

void free_token(void *ptr)
{
	t_token *token;

	token = (t_token *)ptr;
	free(token->value);
	free(token->error);
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