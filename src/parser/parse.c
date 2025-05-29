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
	while (p->current && p->current->type == TKN_PIPE)
	{
		advance(p); // consume '|'
		t_ast *right = parse_command(p);
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

		t_ast *redir_node = ast_binary_op(type, op, cmd, file_node);
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
	ft_lstclear(&argv_list, free);
	return ast_cmd(argv);
}

// // Parse redirection: ('<' | '>' | '>>' | '<<') WORD
// t_ast *parse_redirection(t_parser *p) {
// 	t_token *tok = p->current;
// 	if (!tok || (tok->type != TKN_REDIR_IN && tok->type != TKN_REDIR_OUT
// 			&& tok->type != TKN_APPEND && tok->type != TKN_HEREDOC)) {
// 		return ast_error("Expected redirection");
// 	}
// 	t_ast_type type;
// 	switch (tok->type) {
// 		case TKN_REDIR_IN: type = AST_REDIR_IN; break;
// 		case TKN_REDIR_OUT: type = AST_REDIR_OUT; break;
// 		case TKN_APPEND: type = AST_APPEND; break;
// 		case TKN_HEREDOC: type = AST_HEREDOC; break;
// 		default: return ast_error("Unknown redirection");
// 	}
// 	char *op = strdup(tok->value);
// 	advance(p);

// 	if (!p->current || p->current->type != TKN_WORD) {
// 		free(op);
// 		return ast_error("Expected filename after redirection");
// 	}
// 	char *filename = strdup(p->current->value);
// 	advance(p);

// 	t_ast *file_node = ast_new(AST_LITERAL, filename);
// 	free(filename);

// 	t_ast *redir_node = ast_binary_op(type, op, NULL, file_node);
// 	free(op);
// 	return redir_node;
// }