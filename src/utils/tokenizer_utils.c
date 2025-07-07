#include "minishell.h"

int is_operator_char(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

int is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// is const char **p -> modify char* pointer of line but not the chars inside
char *read_word(const char *line, const char **p)
{
	const char	*start = *p;

	// skips quotes
	while (**p && !is_whitespace(**p) && **p != '\'' && **p != '"' && !is_operator_char(**p))
		(*p)++;
	return (ft_substr(line, start - line, *p - start));
}

// handles also 2-char operators (>>, <<, ||, &&)
char *read_operator(const char *line, const char **p)
{
	const char	*start = *p;

	if (is_operator_char(**p) && *(*p + 1) == **p)
		*p += 2;
	else
		(*p)++;
	return (ft_substr(line, start - line, *p - start));
}

//handles single and double quotes
char *read_quoted(const char *line, const char **p, char quote)
{
	const char *start = *p;

	(*p)++;
	while (**p && **p != quote)
		(*p)++;
	if (**p == quote)
		(*p)++;
	// else = unclosed quote
	return (ft_substr(line, start - line, *p - start));
}

// OBSOLETE: use print_raw_tokens
// void print_tokens(t_list* tokens)
// {
// 	if (!tokens)
// 		print_error("no tokens");
// 	printf("==== print tokens ====\n");
// 	while (tokens != NULL)
// 	{
// 		printf("%s\n", (char *)tokens->content);
// 		tokens = tokens->next;
// 	}
// 	printf("==== end of tokens ====\n");
// }