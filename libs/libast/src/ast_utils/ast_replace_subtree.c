#include "ast.h"

// assuming both are trees (and therefore malloc'ed)
void ast_replace_subtree(t_ast **target, t_ast *replace)
{
	if (!target || *target == replace)
		return ;
	ast_free(*target);
	*target = replace;
}
