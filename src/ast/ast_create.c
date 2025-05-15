#include "ast.h"

t_ast *ast_new(t_ast_type type, char *value)
{
	t_ast *node;

	node = (t_ast *)malloc(sizeof(t_ast));
	if (!node)
		return (NULL);
	node->value = value;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	node->error = NULL;
	node->argv = NULL;
	return (node);
}

t_ast *ast_cmd(char **argv)
{
	t_ast *cmd;

	if (!argv || !argv[0])
		return (NULL);
	cmd = ast_new(AST_COMMAND, ft_strdup(argv[0]));
	if (!cmd)
		return (NULL);
	cmd->argv = argv;
	return (cmd);
}

t_ast *ast_error(char *msg)
{
	t_ast *error_node = ast_new(AST_ERROR, NULL);
	if (!error_node)
		return (NULL);
	error_node->error = ft_strdup(msg);
	if (!error_node->error)
		return (free(error_node), NULL);
	return (error_node);
}

t_ast *ast_binary_op(t_ast_type type, char *op, t_ast *left, t_ast *right)
{
	t_ast *opnode = ast_new(type, op);
	if (!opnode)
		return (free_ast(left), free_ast(right), NULL);
	opnode->left = left;
	opnode->right = right;
	return (opnode);
}