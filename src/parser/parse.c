#include "minishell.h"

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
			return (ast_free(left), ast_error("Missing command after pipe"));
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
	while (p->current && tkn_is_redirection(p->current))
	{
		t_token *tok = p->current;
		advance(p);

		if (!p->current || p->current->type != TKN_WORD)
			return (ast_free(cmd), ast_error("Expected filename after redirection"));

		char *op = strdup(tok->value);
		char *filename = strdup(p->current->value);
		advance(p);

		t_ast *file_node = ast_new(AST_LITERAL, filename);
		t_ast_type type;

		if (tkn_is_redirection(tok))
			type = (t_ast_type)tok->type;
		else
			return (free(op), free(filename), ast_free(cmd), ast_free(file_node),
					ast_error("Unknown redirection"));

		t_ast *redir_node = ast_binary_op(type, op, astdup(cmd), file_node);
		ast_free(cmd);
		if (!redir_node)
			return (ast_free(file_node), NULL);
		cmd = redir_node;
		free(filename);
		free(op);
	}
	return cmd;
}

// Parse a simple command: WORD+
t_ast	*parse_simple_command(t_parser *p)
{
	char	**argv;
	t_ast	*cmd;
	t_list	*argv_list;

	if (!p->current || p->current->type != TKN_WORD)
		return (ast_error("Expected command"));
	argv_list = NULL;
	while (p->current && p->current->type == TKN_WORD)
	{
		ft_lstadd_back(&argv_list, ft_lstnew(strdup(p->current->value)));
		advance(p);
	}
	argv = (char **)lst_to_array(argv_list);
	ft_lstclear(&argv_list, NULL);
	cmd = ast_cmd(argv);
	mtxfree_str(argv);
	return (cmd);
}
