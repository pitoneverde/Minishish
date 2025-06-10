#include "minishell.h"

t_ast *parse_command(t_parser *p);
t_ast *parse_simple_command(t_parser *p);
t_ast *parse_pipeline(t_parser *p);

// driver
t_ast *parse(t_list *lexemes)
{
	t_parser parser;
	parser.tokens = lexemes;
	if (lexemes)
		parser.current = (t_token *)lexemes->content;
	else
		parser.current = NULL;
	return parse_pipeline(&parser);
}

// Parse a pipeline: command '|' command
t_ast *parse_pipeline(t_parser *p)
{
	t_ast *left = parse_command(p);
	if (!left)
		return NULL;

	while (p->current && p->current->type == TKN_PIPE)
	{
		advance(p); // consume '|'
		t_ast *right = parse_command(p);
		if (!right)
			return (free(left), ast_error("Missing command after pipe"));
		left = ast_binary_op(AST_PIPE, "|", left, right);
	}
	return left;
}

// Parse a command: simple_command redirection*
t_ast *parse_command(t_parser *p)
{
	t_ast *cmd = parse_simple_command(p);
	if (!cmd)
		return NULL;

	while (p->current && (p->current->type == TKN_REDIR_IN ||
						  p->current->type == TKN_REDIR_OUT ||
						  p->current->type == TKN_APPEND ||
						  p->current->type == TKN_HEREDOC))
	{
		t_token *tok = p->current;
		advance(p);

		if (!p->current || p->current->type != TKN_WORD)
			return ast_error("Expected filename after redirection");

		char *op = strdup(tok->value);
		char *filename = strdup(p->current->value);
		advance(p);

		t_ast *file_node = ast_new(AST_LITERAL, filename);
		t_ast_type type;

		switch (tok->type) {
			case TKN_REDIR_IN: type = AST_REDIR_IN; break;
			case TKN_REDIR_OUT: type = AST_REDIR_OUT; break;
			case TKN_APPEND: type = AST_APPEND; break;
			case TKN_HEREDOC: type = AST_HEREDOC; break;
			default: return ast_error("Unknown redirection");
		}

		t_ast *redir_node = ast_binary_op(type, op, astdup(cmd), file_node);
		if (!redir_node)
			return (NULL);
		cmd = redir_node;

		free(filename);
		free(op);
	}
	return cmd;
}

// Parse a simple command: WORD+
t_ast *parse_simple_command(t_parser *p)
{
	if (!p->current || p->current->type != TKN_WORD)
		return ast_error("Expected command");

	t_list *argv_list = NULL;

	while (p->current && p->current->type == TKN_WORD)
	{
		ft_lstadd_back(&argv_list, ft_lstnew(strdup(p->current->value)));
		advance(p);
	}
	char **argv = (char **)lst_to_array(argv_list);
	ft_lstclear(&argv_list, NULL);
	return ast_cmd(argv);
}
