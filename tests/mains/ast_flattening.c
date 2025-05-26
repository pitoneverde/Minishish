#include "ast.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

// ---------------------------
// Helpers
// ---------------------------

static const char *safe_node_label(const t_ast *node)
{
	if (!node)
		return "(null)";
	if (node->argv && node->argv[0])
		return node->argv[0];
	if (node->value)
		return node->value;
	return node_type_name(node->type);
}

static void print_node_array(const char *label, t_ast **nodes, size_t count)
{
	printf("%s (%zu node%s):\n", label, count, count == 1 ? "" : "s");
	for (size_t i = 0; i < count; i++)
		printf(" - [%zu] %s\n", i, safe_node_label(nodes[i]));
}

// ---------------------------
// AST construction
// ---------------------------

static t_ast *build_leaf_test_tree(void)
{
	t_ast *cmd1 = ast_cmd((char *[]){"echo", "hello", NULL});
	t_ast *cmd2 = ast_cmd((char *[]){"grep", "h", NULL});
	t_ast *cmd3 = ast_cmd((char *[]){"wc", "-l", NULL});
	t_ast *pipe1 = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
	return ast_binary_op(AST_PIPE, "|", pipe1, cmd3);
}

static t_ast *build_unbalanced_tree(void)
{
	t_ast *cmd1 = ast_cmd((char *[]){"ls", NULL});
	t_ast *cmd2 = ast_cmd((char *[]){"sort", NULL});
	t_ast *cmd3 = ast_cmd((char *[]){"uniq", NULL});
	t_ast *out = ast_new(AST_LITERAL, "output.txt");
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", cmd3, out);
	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, cmd2);
	return ast_binary_op(AST_PIPE, "|", pipe, redir);
}

static t_ast *build_error_and_literal_tree(void)
{
	t_ast *literal = ast_new(AST_LITERAL, "file.txt");
	t_ast *error = ast_error("invalid token");
	return ast_binary_op(AST_REDIR_IN, "<", literal, error);
}

// ---------------------------
// Leaf test
// ---------------------------

static void test_leaf_nodes(void)
{
	printf("\n[TEST] Leaf Node Collection\n");

	// Edge: NULL input
	assert(ast_leaf_nodes(NULL) == NULL);

	// Test: normal tree
	t_ast *tree = build_leaf_test_tree();
	size_t leaf_count = 0;
	t_ast **leaves = ast_leaf_nodes_n(tree, &leaf_count);
	assert(leaf_count == 3);
	assert(leaves != NULL);

	print_node_array("Leaf nodes", leaves, leaf_count);

	// Ensure all are command nodes and match original tree leaves
	assert(leaves[0]->type == AST_COMMAND);
	assert(leaves[1]->type == AST_COMMAND);
	assert(leaves[2]->type == AST_COMMAND);
	assert(leaves[0]->argv && strcmp(leaves[0]->argv[0], "echo") == 0);
	assert(leaves[2]->argv && strcmp(leaves[2]->argv[0], "wc") == 0);

	free(leaves);
	ast_free(tree);
}

// ---------------------------
// Flatten test
// ---------------------------

static void test_flatten_ast(void)
{
	printf("\n[TEST] AST Flattening\n");

	// Edge: NULL input
	assert(ast_flatten_pre(NULL, NULL) == NULL);

	t_ast *tree = build_unbalanced_tree();

	size_t pre_count = 0, post_count = 0;
	t_ast **pre = ast_flatten_pre(tree, &pre_count);
	t_ast **post = ast_flatten_post(tree, &post_count);

	assert(pre && post);
	assert(pre_count == post_count); // Must match node count

	print_node_array("Flatten pre-order", pre, pre_count);
	print_node_array("Flatten post-order", post, post_count);

	printf("root: %p\n", (void *)tree);
	printf("pre[0]: %p\n", (void *)pre[0]);
	// Ensure root is first in pre-order and last in post-order
	assert(pre[0] == tree);
	assert(post[post_count - 1] == tree);

	// All pointers must be in original AST
	for (size_t i = 0; i < pre_count; i++)
		assert(pre[i] != NULL && post[i] != NULL);

	free(pre);
	free(post);
	ast_free(tree);
}

// ---------------------------
// Error and literal edge cases
// ---------------------------

static void test_error_and_literal_tree(void)
{
	printf("\n[TEST] Literal and Error Node Edge Case\n");

	t_ast *tree = build_error_and_literal_tree();
	assert(tree->type == AST_REDIR_IN);

	size_t leaf_count = 0;
	t_ast **leaves = ast_leaf_nodes_n(tree, &leaf_count);
	assert(leaf_count == 2);
	assert(leaves[0]->type == AST_LITERAL);
	assert(leaves[1]->type == AST_ERROR);

	print_node_array("Leaf nodes with literal and error", leaves, leaf_count);

	size_t flat_count = 0;
	t_ast **flat = ast_flatten_pre(tree, &flat_count);
	assert(flat_count == 3); // redir + 2 children

	print_node_array("Flattened with error/literal", flat, flat_count);

	free(leaves);
	free(flat);
	ast_free(tree);
}

// ---------------------------
// Main test driver
// ---------------------------

int main(void)
{
	test_leaf_nodes();
	test_flatten_ast();
	test_error_and_literal_tree();

	printf("\nAll tests passed ✅\n");
	return 0;
}
