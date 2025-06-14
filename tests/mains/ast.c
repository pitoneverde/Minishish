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

// 	ast_free(pipe); // Frees everything
// 	return (0);
// }

// ls -l | grep .c > out.txt
// int main(void)
// {
// 	char **argv;
// 	argv = (char *[]){"ls", "-la", NULL};
// 	t_ast *cmd1 = ast_cmd(argv);
// 	argv = (char *[]){"grep", ".c", NULL};
// 	t_ast *cmd2 = ast_cmd(argv);
// 	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
// 	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", pipe, ast_new(AST_LITERAL, "out.txt"));
// 	print_ast(redir, 0);
// 	ast_free(redir);
// }

// doing the same with Unity testing:
#include "unity.h"
#include "libft.h"

static void assert_command_args(t_ast *cmd, char **e_args, int e_argc);
static t_list *argv_to_ast_list(char **argv);
static t_ast *build_sample_ast(void);

static void assert_command_args(t_ast *cmd, char **e_args, int e_argc)
{
	int		i;
	t_ast	*arg_ast;
	t_list	*arg_node;

	TEST_ASSERT_EQUAL_INT(AST_COMMAND, cmd->type);
	TEST_ASSERT_EQUAL_INT(e_argc, cmd->argc);

	// check argv (post-expansion)
	if (cmd->argv)
	{
		i = 0;
		while (i < e_argc)
		{
			TEST_ASSERT_EQUAL_STRING(e_args[i], cmd->argv[i]);
			i++;
		}
	}

	// check args (pre-expansion)
	arg_node = cmd->args;
	i = 0;
	while (i < e_argc)
	{
		TEST_ASSERT_NOT_NULL(arg_node);
		arg_ast = (t_ast *)arg_node->content;
		TEST_ASSERT_EQUAL_INT(AST_LITERAL, arg_ast->type);
		TEST_ASSERT_EQUAL_STRING(e_args[i], arg_ast->value);
		arg_node = arg_node->next;
		i++;
	}
	TEST_ASSERT_NULL(arg_node);	//end of list
}

static t_list *argv_to_ast_list(char **argv)
{
	t_list *lst = NULL;
	for (int i = 0; argv[i] != NULL; i++)
	{
		t_ast *lit = ast_new(AST_LITERAL, argv[i]);
		t_list *node = ft_lstnew(lit);
		ft_lstadd_back(&lst, node);
	}
	return lst;
}

// ls -l | grep .c > out.txt
static t_ast *build_sample_ast(void)
{
	char *argv1[] = {"ls", "-la", NULL};
	char *argv2[] = {"grep", ".c", NULL};

	t_list *list1 = argv_to_ast_list(argv1);
	t_list *list2 = argv_to_ast_list(argv2);

	t_ast *cmd1 = ast_cmd(list1);
	t_ast *cmd2 = ast_cmd(list2);

	ft_lstclear(&list1, (void (*)(void *))ast_free);
	ft_lstclear(&list2, (void (*)(void *))ast_free);

	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", pipe, ast_new(AST_LITERAL, "out.txt"));

	return redir;
}

void test_sample_ast_building(void)
{
	t_ast *redir = build_test_ast();
	TEST_ASSERT_EQUAL_INT(AST_REDIR_OUT, redir->type);
	TEST_ASSERT_EQUAL_STRING(">", redir->value);

	t_ast *pipe = redir->left;
	TEST_ASSERT_NOT_NULL(pipe);
	TEST_ASSERT_EQUAL_INT(AST_PIPE, pipe->type);
	TEST_ASSERT_EQUAL_STRING("|", pipe->value);

	t_ast *cmd1 = pipe->left;
	t_ast *cmd2 = pipe->right;

	const char *cmd1_args[] = {"ls", "-la"};
	const char *cmd2_args[] = {"grep", ".c"};

	assert_command_args(cmd1, cmd1_args, 2);
	assert_command_args(cmd2, cmd2_args, 2);

	t_ast *outfile = redir->right;
	TEST_ASSERT_NOT_NULL(outfile);
	TEST_ASSERT_EQUAL_INT(AST_LITERAL, outfile->type);
	TEST_ASSERT_EQUAL_STRING("out.txt", outfile->value);

	ast_free(redir);
}
