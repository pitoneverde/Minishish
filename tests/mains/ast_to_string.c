#include "ast.h"

void test_simple_command()
{
	char *argv[] = {"echo", "hello", NULL};
	t_ast *cmd = ast_cmd(argv);
	char *str = ast_to_string(cmd);
	printf("Simple command:\n%s\n\n", str);
	free(str);
	ast_free(cmd);
}

void test_pipe_command()
{
	char *argv1[] = {"ls", "-l", NULL};
	char *argv2[] = {"grep", "txt", NULL};

	t_ast *left = ast_cmd(argv1);
	t_ast *right = ast_cmd(argv2);
	t_ast *pipe = ast_binary_op(AST_PIPE, "|", left, right);

	char *str = ast_to_string(pipe);
	printf("Pipe command:\n%s\n\n", str);
	free(str);
	ast_free(pipe);
}

void test_redirection()
{
	char *argv[] = {"cat", NULL};
	t_ast *cmd = ast_cmd(argv);
	t_ast *file = ast_new(AST_LITERAL, "file.txt");
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", cmd, file);

	char *str = ast_to_string(redir);
	printf("Redirection command:\n%s\n\n", str);
	free(str);
	ast_free(redir);
}

void test_nested_pipeline_with_redirection()
{
	char *argv1[] = {"ps", "aux", NULL};
	char *argv2[] = {"grep", "root", NULL};
	char *argv3[] = {"wc", "-l", NULL};

	t_ast *n1 = ast_cmd(argv1);
	t_ast *n2 = ast_cmd(argv2);
	t_ast *n3 = ast_cmd(argv3);

	t_ast *pipe1 = ast_binary_op(AST_PIPE, "|", n1, n2);
	t_ast *pipe2 = ast_binary_op(AST_PIPE, "|", pipe1, n3);

	char *str = ast_to_string(pipe2);
	printf("Nested pipeline:\n%s\n\n", str);
	free(str);
	ast_free(pipe2);
}

void test_error_node()
{
	t_ast *err = ast_error("Unexpected token");
	char *str = ast_to_string(err);
	printf("Error node:\n%s\n\n", str);
	free(str);
	ast_free(err);
}

void test_null_node()
{
	char *str = ast_to_string(NULL);
	printf("Null node:\n%s\n\n", str);
	free(str);
}

// int main(void)
// {
// 	test_simple_command();
// 	test_pipe_command();
// 	test_redirection();
// 	test_nested_pipeline_with_redirection();
// 	test_error_node();
// 	test_null_node();
// 	return 0;
// }

// #include "ast.h"

// static void print_node_verbose(const t_ast *node, int depth)
// {
// 	if (!node)
// 	{
// 		printf("%*s(null)\n", depth * 2, "");
// 		return;
// 	}
// 	printf("%*sNode type: %s\n", depth * 2, "", node_type_name(node->type));
// 	printf("%*sValue: %s\n", depth * 2, "", node->value ? node->value : "(null)");
// 	if (node->argv)
// 	{
// 		printf("%*sArgv: [", depth * 2, "");
// 		for (int i = 0; node->argv[i]; i++)
// 			printf("\"%s\"%s", node->argv[i], node->argv[i + 1] ? ", " : "");
// 		printf("]\n");
// 	}
// 	if (node->error)
// 		printf("%*sError: %s\n", depth * 2, "", node->error);
// 	if (node->left || node->right)
// 	{
// 		printf("%*sLeft:\n", depth * 2, "");
// 		print_node_verbose(node->left, depth + 1);
// 		printf("%*sRight:\n", depth * 2, "");
// 		print_node_verbose(node->right, depth + 1);
// 	}
// }

// int main(void)
// {
// 	// 1. Create a sample AST: ls -l | grep .c > out.txt
// 	char *argv1[] = {"ls", "-l", NULL};
// 	char *argv2[] = {"grep", ".c", NULL};
// 	t_ast *cmd1 = ast_cmd(argv1);
// 	t_ast *cmd2 = ast_cmd(argv2);
// 	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
// 	t_ast *output = ast_new(AST_LITERAL, "out.txt");
// 	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", pipe, output);

// 	// 2. Create an error node
// 	t_ast *err = ast_error("Invalid syntax");

// 	// 3. Print original AST
// 	printf("\n=== Original AST ===\n");
// 	print_ast(redir, 0);

// 	// 4. Print verbose info
// 	printf("\n=== Verbose Node Dump ===\n");
// 	print_node_verbose(redir, 0);

// 	// 5. Call ast_to_string
// 	printf("\n=== AST String Representation ===\n");
// 	char *str = ast_to_string(redir);
// 	if (!str)
// 		printf("ast_to_string returned NULL\n");
// 	else
// 	{
// 		printf("Result: \"%s\"\n", str);
// 		free(str);
// 	}

// 	// 6. Test error node stringification
// 	printf("\n=== AST Error String Representation ===\n");
// 	char *err_str = ast_to_string(err);
// 	if (!err_str)
// 		printf("ast_to_string (error node) returned NULL\n");
// 	else
// 	{
// 		printf("Error result: \"%s\"\n", err_str);
// 		free(err_str);
// 	}

// 	// 7. Clean up
// 	ast_free(redir);
// 	ast_free(err);

// 	return 0;
// }
