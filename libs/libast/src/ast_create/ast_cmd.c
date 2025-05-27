#include "ast.h"

t_ast *ast_cmd(char **argv)
{
	t_ast *cmd;

	if (!argv || !argv[0])
		return (NULL);
	cmd = ast_new(AST_COMMAND, argv[0]);
	if (!cmd)
		return (NULL);
	cmd->argv = mtxdup_str(argv);
	return (cmd);
}