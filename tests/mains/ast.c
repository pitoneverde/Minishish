// !! IMPORTANT !!
// RAW AST EXAMPLE, BELOW THIS THE ONE WITH QoL ENHANCEMENTS
#include "ast.h"
#include <stdio.h>
#include <string.h>

// int main(void)
// {
// 	t_ast *cmd1 = ast_new(AST_COMMAND, ft_strdup("echo"));
// 	t_ast *arg1 = ast_new(AST_COMMAND, ft_strdup("hello"));

// 	t_ast *pipe = ast_new(AST_PIPE, ft_strdup("|"));

// 	t_ast *cmd2 = ast_new(AST_COMMAND, ft_strdup("grep"));
// 	t_ast *arg2 = ast_new(AST_COMMAND, ft_strdup("h"));

// 	ast_attach_left(cmd1, arg1);  // echo -> hello
// 	ast_attach_left(cmd2, arg2);  // grep -> h
// 	ast_attach_left(pipe, cmd1);  // pipe -> echo
// 	ast_attach_right(pipe, cmd2); // pipe -> grep

// 	print_ast(pipe, 0);

// 	free_ast(pipe); // Frees everything
// 	return (0);
// }

int main(void)
{
	char **argv;
	// size_t count;
	argv = (char *[]){"ls", "-la", NULL};
	// ls -l | grep .c > out.txt
	t_ast *cmd1 = ast_cmd(argv);
	argv = (char *[]){"grep", ".c", NULL};
	t_ast *cmd2 = ast_cmd(argv);
	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", pipe, ast_new(AST_LITERAL, "out.txt"));
	print_ast(redir, 0);
	free_ast(redir);
}