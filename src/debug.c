#include "minishell.h"
const char *token_type_name(t_token_type type)
{
	if (type == TKN_WORD)
		return "WORD";
	if (type == TKN_PIPE)
		return "PIPE";
	if (type == TKN_REDIRECT_IN)
		return "REDIRECT_IN";
	if (type == TKN_REDIRECT_OUT)
		return "REDIRECT_OUT";
	if (type == TKN_APPEND)
		return "APPEND";
	if (type == TKN_HEREDOC)
		return "HEREDOC";
	if (type == TKN_S_QUOTED)
		return "SINGLE QUOTED";
	if (type == TKN_D_QUOTED)
		return "DOUBLE QUOTED";
	if (type == TKN_ERROR)
		return "ERROR";
	return "UNKNOWN";
}

void print_lexed_tokens(t_list *tokens)
{
	while (tokens)
	{
		t_token *tok = (t_token *)tokens->content;
		printf("Type: %-13s Value: \"%s\"\n", token_type_name(tok->type), tok->value);
		if (tok->error)
			printf("\t->Error: %s\n", tok->error);
		tokens = tokens->next;
	}
}

void print_token_errors(t_list *lexemes)
{
	while (lexemes)
	{
		t_token *tok = lexemes->content;
		if (tok->error)
			fprintf(stderr, "minishell: %s\n", tok->error);
		lexemes = lexemes->next;
	}
}

void print_raw_tokens(t_list *tokens)
{
	while (tokens)
	{
		printf("Raw token: \"%s\"\n", (char *)tokens->content);
		tokens = tokens->next;
	}
}