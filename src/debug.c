#include "minishell.h"

static void print_arg_node(void *content);

void print_raw_tokens(t_list *tokens)
{
	while (tokens)
	{
		printf("Raw token: \"%s\"\n", (char *)tokens->content);
		tokens = tokens->next;
	}
}

const char *token_type_name(t_token_type type)
{
	if (type == TKN_WORD)
		return "WORD";
	if (type == TKN_PIPE)
		return "PIPE";
	if (type == TKN_REDIR_IN)
		return "REDIRECT_IN";
	if (type == TKN_REDIR_OUT)
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

// void print_token_errors(t_list *lexemes)
// {
// 	while (lexemes)
// 	{
// 		t_token *tok = lexemes->content;
// 		if (tok->error)
// 			fprintf(stderr, "minishell: %s\n", tok->error);
// 		lexemes = lexemes->next;
// 	}
// }

const char *node_type_name(t_ast_type type)
{
	if (type == AST_COMMAND)
		return ("COMMAND");
	if (type == AST_PIPE)
		return ("PIPE");
	if (type == AST_REDIR_IN)
		return ("REDIRECT IN");
	if (type == AST_REDIR_OUT)
		return ("REDIRECT OUT");
	if (type == AST_APPEND)
		return ("APPEND");
	if (type == AST_HEREDOC)
		return ("HEREDOC");
	if (type == AST_ERROR)
		return ("ERROR");
	if (type == AST_LITERAL)
		return ("LITERAL");
	return ("UNKNOWN");
}

// recursively print the Absract Syntax Tree
void print_ast(const t_ast *node, int depth)
{
	if (!node)
		return;

	for (int i = 0; i < depth; i++)
		printf("  ");

	printf("(%s", node_type_name(node->type));

	if (node->value)
		printf(", value: \"%s\"", node->value);

	if (node->error)
		printf(" -> Error: %s", node->error);

	printf(")\n");

	// Print arguments if this is a command node
	if (node->type == AST_COMMAND && node->args)
	{
		for (int i = 0; i < depth + 1; i++)
			printf("  ");
		printf("Args:\n");

		ft_lstiter(node->args, print_arg_node);
	}

	// Recurse on children
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

static void print_arg_node(void *content)
{
	const t_ast *arg = (const t_ast *)content;

	printf("    - \"%s\"", arg->value);
	if (arg->quote == S_QUOTE)
		printf(" (single quoted)");
	else if (arg->quote == D_QUOTE)
		printf(" (double quoted)");
	printf("\n");
}