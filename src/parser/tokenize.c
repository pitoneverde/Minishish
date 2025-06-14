#include "minishell.h"
// TODO: now parses only words, and operators, add quotes
t_list *tokenize(const char *line)
{
	t_list		*tokens;
	t_list		*new_token;
	char		*word;
	const char	*p = line;

	if (!line)
		return (NULL);
	tokens = NULL;
	while (*p)
	{
		while(is_whitespace(*p))
			p++;
		if(*p == '\0')
			break ;
		word = read_next_token(line, &p);
		if (!word)
			return (free_raw_tokens(&tokens), NULL);
		new_token = ft_lstnew(word);
		if (!new_token)
			return (free(word), free_raw_tokens(&tokens), NULL);
		ft_lstadd_back(&tokens, new_token);
	}
	return (tokens);
}

char *read_next_token(const char *line, const char **p)
{
	if (**p == '\'' || **p == '"')
		return read_quoted(line, p, **p);
	else if (is_operator_char(**p))
		return read_operator(line, p);
	else
		return read_word(line, p);
}

void free_raw_tokens(t_list **tokens)
{
	ft_lstclear(tokens, free);
}