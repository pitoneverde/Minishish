#include <stdio.h>
#include <string.h>
#include "ast.h"
#include "libft.h"
#include "unity.h"

static void assert_command_args(t_ast *cmd, char **e_args, int e_argc);
static t_list *argv_to_ast_list(char **argv);
static t_ast *build_sample_ast(void);

void test_sample_ast_building(void)
{
	t_ast *redir = build_sample_ast();
	TEST_ASSERT_EQUAL_INT(AST_REDIR_OUT, redir->type);
	TEST_ASSERT_EQUAL_STRING(">", redir->value);

	t_ast *pipe = redir->left;
	TEST_ASSERT_NOT_NULL(pipe);
	TEST_ASSERT_EQUAL_INT(AST_PIPE, pipe->type);
	TEST_ASSERT_EQUAL_STRING("|", pipe->value);

	t_ast *cmd1 = pipe->left;
	t_ast *cmd2 = pipe->right;

	char *cmd1_args[] = {"ls", "-la", NULL};
	char *cmd2_args[] = {"grep", ".c", NULL};

	assert_command_args(cmd1, cmd1_args, 2);
	assert_command_args(cmd2, cmd2_args, 2);

	t_ast *outfile = redir->right;
	TEST_ASSERT_NOT_NULL(outfile);
	TEST_ASSERT_EQUAL_INT(AST_LITERAL, outfile->type);
	TEST_ASSERT_EQUAL_STRING("out.txt", outfile->value);

	ast_free(redir);
}
static t_list *argv_to_ast_list(char **argv)
{
	t_list *lst = NULL;
	for (int i = 0; argv[i] != NULL; i++)
	{
		printf("Creating AST_LITERAL for arg: %s\n", argv[i]);
		t_ast *lit = ast_new(AST_LITERAL, argv[i]);
		if (!lit)
		{
			printf("Failed to create AST_LITERAL node\n");
			// Handle error or exit test
		}
		else if (!lit->value)
		{
			printf("Warning: lit->value is NULL for arg: %s\n", argv[i]);
		}
		t_list *node = ft_lstnew(lit);
		ft_lstadd_back(&lst, node);
	}
	return lst;
}

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
		while (e_args[i] && i < e_argc)
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

// ls -l | grep .c > out.txt
static t_ast *build_sample_ast(void)
{
	char *argv1[] = {"ls", "-la", NULL};
	char *argv2[] = {"grep", ".c", NULL};

	t_list *list1 = argv_to_ast_list(argv1);
	t_list *list2 = argv_to_ast_list(argv2);
	
	t_ast *cmd1 = ast_cmd(list1);
	t_ast *cmd2 = ast_cmd(list2);

	ft_lstclear(&list1, free);
	ft_lstclear(&list2, free);

	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", pipe, ast_new(AST_LITERAL, "out.txt"));

	return redir;
}
