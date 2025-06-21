#include "ast.h"
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_NODES 100

static t_ast_type visited[MAX_NODES];
static size_t visited_index = 0;

void reset_visited(void) {
	visited_index = 0;
	memset(visited, 0, sizeof(visited));
}

void record_visit(t_ast *node) {
	if (visited_index < MAX_NODES)
		visited[visited_index++] = node->type;
}

void print_traversal(const char *label) {
	printf("%s order: ", label);
	for (size_t i = 0; i < visited_index; ++i) {
		printf("%s ", node_type_name(visited[i]));
	}
	printf("\n");
}

int main(void) {
	// AST: PIPE(COMMAND("ls"), REDIR_OUT(COMMAND("out"), LITERAL("file.txt")))
	t_ast *cmd1 = ast_cmd((char *[]){ "ls", NULL });
	t_ast *cmd2 = ast_cmd((char *[]){ "out", NULL });
	t_ast *file = ast_new(AST_LITERAL, "file.txt");
	t_ast *redir = ast_binary_op(AST_REDIR_OUT, ">", cmd2, file);
	t_ast *pipe = ast_binary_op(AST_PIPE, "|", cmd1, redir);

	// Test pre-order
	reset_visited();
	astt_pre(pipe, record_visit);
	print_traversal("Pre");

	// Test post-order
	reset_visited();
	astt_post(pipe, record_visit);
	print_traversal("Post");

	// Edge case: NULL input
	reset_visited();
	astt_pre(NULL, record_visit);
	assert(visited_index == 0);

	// Cleanup
	ast_free(pipe);

	return 0;
}
