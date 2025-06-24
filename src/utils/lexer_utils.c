#include "minishell.h"

// add strncmp of && and || if gonna do bonus
t_token_type classify_token(const char *raw_token)
{
	size_t len;

	if(!raw_token)
		return TKN_WORD;
	len = ft_strlen(raw_token);
	if (len == 2 && ft_strncmp(raw_token, ">>", 2) == 0)
		return TKN_APPEND;
	if (len == 2 && ft_strncmp(raw_token, "<<", 2) == 0)
		return TKN_HEREDOC;
	if (len == 1 && raw_token[0] == '|')
		return TKN_PIPE;
	if (len == 1 && raw_token[0] == '>')
		return TKN_REDIR_OUT;
	if (len == 1 && raw_token[0] == '<')
		return TKN_REDIR_IN;
	if (is_malformed(raw_token, len))
		return TKN_ERROR;
	return TKN_WORD;
}

t_quote_type classify_quote(const char *raw_token)
{
	size_t	len;

	len = ft_strlen(raw_token);
	if (len >= 2 && is_quoted(raw_token, len, '\''))
		return (S_QUOTE);
	if (len >= 2 && is_quoted(raw_token, len, '"'))
		return (D_QUOTE);
	return (N_QUOTE);
}

int is_quoted(const char *raw_token, int len, char quote)
{
	return (raw_token[0] == quote && raw_token[len - 1] == quote);
}

int is_malformed(const char *raw_token, int len)
{
	return ((raw_token[0] == '\'' && raw_token[len - 1] != '\'')
			|| (raw_token[0] == '"' && raw_token[len - 1] != '"')
			|| (raw_token[0] != '\'' && raw_token[len - 1] == '\'')
			|| (raw_token[0] != '"' && raw_token[len - 1] == '"'));
}