#include "ast.h"

// create command node
// args must be a list of AST_LITERAL nodes
t_ast *ast_cmd(t_list *args)
{
	t_ast *cmd;
	
	cmd = ast_new(AST_COMMAND, NULL);
	if (!cmd)
		return (NULL);
	
	cmd->args = args;
	cmd->argc = ft_lstsize(args);

	if (cmd->argc > 0)
		cmd->value = ft_strdup(((t_ast *)args->content)->value);
	return (cmd);
}