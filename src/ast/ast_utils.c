#include "ast.h"

// assuming both are trees (and therefore malloc'ed)
void ast_replace_subtree(t_ast **target, t_ast *replace)
{
	if (!target || *target == replace)
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

// search in node->value
int ast_find(t_ast *node, const char *value)
{
	if (!node)
		return (0);
	if (node->value && ft_strncmp(node->value, value, ft_strlen(value)))
		return (1);
	return ast_find(node->left, value) || ast_find(node->right, value);
}

char *ast_to_string(const t_ast *node)
{
	t_ast *clone;
	char *res;

	clone = astdup(node);
	if (!clone)
		return (NULL);
	ast_stringify(clone);
	if (!clone->value)
		return (free_ast(clone), NULL);
	res = ft_strdup(clone->value);
	return (free_ast(clone), res);
}
