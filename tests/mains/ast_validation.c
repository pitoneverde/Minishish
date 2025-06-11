#include "ast.h"

void test_valid_ast(const char *label, t_ast *ast, int expected)
{
	int result = ast_is_valid(ast);
	printf("[%s] Valid: %d (expected %d)\n", label, result, expected);
	ast_free(ast);
}

void test_null_ast()
{
	printf("[NULL AST pointer] Valid: %d (expected 0)\n", ast_is_valid(NULL));
}

// BASIC TESTING, BELOW EDGE CASES
// int main(void)
// {
// 	// 1. Valid: simple command
// 	char *argv1[] = {"ls", "-l", NULL};
// 	t_ast *cmd1 = ast_cmd(argv1);
// 	test_valid_ast("simple command", cmd1, 1);

// 	// 2. Invalid: command with NULL argv
// 	t_ast *bad_cmd = ast_cmd(NULL);
// 	test_valid_ast("command with NULL argv", bad_cmd, 0);

// 	// 3. Valid: pipeline
// 	char *argv2[] = {"grep", ".c", NULL};
// 	t_ast *cmd2 = ast_cmd(argv2);
// 	t_ast *pipe = ast_binary_op(AST_PIPE, "|",
// 								ast_cmd((char *[]){"ls", NULL}),
// 								cmd2);
// 	test_valid_ast("pipeline", pipe, 1);

// 	// 4. Invalid: pipe with right side error
// 	t_ast *err = ast_error("missing command");
// 	t_ast *bad_pipe = ast_binary_op(AST_PIPE, "|",
// 									ast_cmd((char *[]){"ls", NULL}), err);
// 	test_valid_ast("pipe with error on right", bad_pipe, 0);

// 	// 5. Valid: redirection
// 	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">",
// 								 ast_cmd((char *[]){"ls", NULL}),
// 								 ast_new(AST_LITERAL, "out.txt"));
// 	test_valid_ast("redir with valid literal", redir, 1);

// 	// 6. Invalid: redirection missing filename (right is NULL)
// 	t_ast *bad_redir = ast_binary_op(AST_REDIR_OUT, ">",
// 									 ast_cmd((char *[]){"ls", NULL}),
// 									 NULL);
// 	test_valid_ast("redir missing target", bad_redir, 0);

// 	// 7. Invalid: redirection target is not a literal
// 	t_ast *bad_redir2 = ast_binary_op(AST_REDIR_OUT, ">",
// 									  ast_cmd((char *[]){"ls", NULL}),
// 									  ast_cmd((char *[]){"not", "a", "literal", NULL}));
// 	test_valid_ast("redir with non-literal right", bad_redir2, 0);

// 	// 8. Invalid: AST_ERROR node
// 	t_ast *only_error = ast_error("bad thing");
// 	test_valid_ast("AST_ERROR node", only_error, 0);

// 	return 0;
// }

int main(void)
{
	// 0. NULL input
	test_null_ast();

	// 1. Valid: simple command
	t_ast *cmd1 = ast_cmd((char *[]){"ls", "-l", NULL});
	test_valid_ast("simple command", cmd1, 1);

	// 2. Invalid: command with NULL argv
	test_valid_ast("command with NULL argv", ast_cmd(NULL), 0);

	// 3. Valid: pipeline
	t_ast *pipe = ast_binary_op(AST_PIPE, "|",
								ast_cmd((char *[]){"ls", NULL}),
								ast_cmd((char *[]){"grep", ".c", NULL}));
	test_valid_ast("pipeline", pipe, 1);

	// 4. Invalid: pipe with right side error
	t_ast *err = ast_error("bad right side");
	t_ast *bad_pipe = ast_binary_op(AST_PIPE, "|",
									ast_cmd((char *[]){"ls", NULL}), err);
	test_valid_ast("pipe with error on right", bad_pipe, 0);

	// 5. Valid: redirection
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">",
								 ast_cmd((char *[]){"ls", NULL}),
								 ast_new(AST_LITERAL, "out.txt"));
	test_valid_ast("redir with valid literal", redir, 1);

	// 6. Invalid: redirection missing target
	t_ast *bad_redir = ast_binary_op(AST_REDIR_OUT, ">",
									 ast_cmd((char *[]){"ls", NULL}), NULL);
	test_valid_ast("redir missing target", bad_redir, 0);

	// 7. Invalid: redirection with NULL left
	t_ast *redir_noleft = ast_binary_op(AST_REDIR_IN, "<", NULL,
										ast_new(AST_LITERAL, "in.txt"));
	test_valid_ast("redir missing left", redir_noleft, 0);

	// 8. Invalid: redirection target is a command
	t_ast *bad_target = ast_binary_op(AST_REDIR_OUT, ">",
									  ast_cmd((char *[]){"echo", "test", NULL}),
									  ast_cmd((char *[]){"oops", NULL}));
	test_valid_ast("redir with command as target", bad_target, 0);

	// 9. Invalid: literal with NULL value
	t_ast *bad_lit = ast_new(AST_LITERAL, NULL);
	test_valid_ast("literal with NULL value", bad_lit, 0);

	// 10. Invalid: pipe with both sides NULL
	t_ast *null_pipe = ast_binary_op(AST_PIPE, "|", NULL, NULL);
	test_valid_ast("pipe with NULL children", null_pipe, 0);

	// 11. Invalid: AST_ERROR node
	t_ast *error_node = ast_error("something went wrong");
	test_valid_ast("AST_ERROR node", error_node, 0);

	return 0;
}
