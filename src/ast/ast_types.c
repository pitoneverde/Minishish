#include "ast.h"

int ast_is_operator(t_ast_type type)
{
	return (type == AST_APPEND || type == AST_HEREDOC ||
			type == AST_PIPE || type == AST_REDIR_IN ||
			type == AST_REDIR_OUT);
}

int ast_is_command(const t_ast *node)
{
	return (node && node->type == AST_COMMAND);
}

// 2: how do i traverse the tree
// 3: how do i validate the tree following my grammar:
// GRAMMAR:
// command      ::= simple_command | pipeline | compound_command
// simple_command ::= WORD { WORD | redirection }
// pipeline     ::= command { '|' command }
// compound_command ::= command ('&&' | '||') command
// redirection  ::= '<' WORD | '>' WORD | '>>' WORD | '<<' WORD
