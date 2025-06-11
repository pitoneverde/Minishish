#include "minishell.h"

static t_ast *parse_redirection(t_parser *p, t_ast *cmd);

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
	t_ast *cmd;

	cmd = parse_simple_command(p);
	if (!cmd)
		return (NULL);
	while (p->current && tkn_is_redirection(p->current))
	{
		cmd = parse_redirection(p, cmd);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
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

// Helper to parse a single redirection and return the updated command node
static t_ast *parse_redirection(t_parser *p, t_ast *cmd)
{
	char *op;
	char *filename;
	t_ast *f_node;
	t_ast *r_node;
	t_token *redir;

	redir = p->current;
	advance(p);
	if (!p->current || p->current->type != TKN_WORD)
		return (ast_free(cmd), ast_error("Expected filename"));
	op = ft_strdup(redir->value);
	filename = ft_strdup(p->current->value);
	f_node = ast_new(AST_LITERAL, filename);
	free(filename);
	advance(p);
	if (!f_node || !tkn_is_redirection(redir))
		return (free(op), ast_free(cmd), ast_free(f_node), ast_error("Error"));
	r_node = ast_binary_op((t_ast_type)redir->type, op, astdup(cmd), f_node);
	ast_free(cmd);
	free(op);
	if (!r_node) // = NULL
		ast_free(f_node);
	return (r_node);
}
