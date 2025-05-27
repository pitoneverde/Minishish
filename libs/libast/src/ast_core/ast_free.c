#include "ast.h"

void ast_free(t_ast *tree)
{
	if (!tree)
		return;
	ast_free(tree->left);
	ast_free(tree->right);
	if (tree->value)
		free(tree->value);
	if (tree->error)
		free(tree->error);
	if (tree->argv)
		mtxfree_str(tree->argv);
	free(tree);
}