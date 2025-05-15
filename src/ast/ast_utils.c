#include "ast.h"

// assuming both are trees (and therefore malloc'ed)
void ast_replace_subtree(t_ast **target, t_ast *replace)
{
	if (!target)
		return ;
	free_ast(*target);
	*target = replace;
}

// behaves like foreach
void ast_map(t_ast *node, void (*f)(t_ast *))
{
	if (!node || !f)
		return ;
	f(node);
	ast_map(node->left, f);
	ast_map(node->right, f);
}