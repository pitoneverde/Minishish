#ifndef AST_H
# define AST_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum e_ast_type
{
	AST_COMMAND,	// TKN_WORD
	AST_LITERAL,	// also TKN_WORD
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_APPEND,
	AST_HEREDOC,
	AST_ERROR
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type		type;
	struct s_ast	*left;
	struct s_ast	*right;
	char			*value;		// "echo", "<<", arguments
	char			**argv;		// only used in AST_COMMAND, default NULL
	char			*error;		// only used in AST_ERROR, default NULL
}	t_ast;

// create
t_ast *ast_new(t_ast_type type, char *value);
t_ast *ast_cmd(char **argv);
t_ast *ast_binary_op(t_ast_type type, char *op, t_ast *left, t_ast *right);
t_ast *ast_error(char *msg);

// core
void ast_attach_left(t_ast *parent, t_ast *child);
void ast_attach_right(t_ast *parent, t_ast *child);
void free_ast(t_ast *tree);
t_ast *astdup(const t_ast *node);

// utils
int ast_find(t_ast *node, const char *value);
void ast_map(t_ast *node, void (*f)(t_ast *));
void ast_replace_subtree(t_ast **target, t_ast *replace);
char *ast_to_string(const t_ast *node);

// to_string
void ast_stringify(t_ast *node);

// types (to move into parser)
int ast_is_operator(t_ast_type type);
int ast_is_command(const t_ast *node);
int ast_is_simple_pipeline(const t_ast *node);
int ast_is_redirection_chain(const t_ast *node);

// errors and validation (also to move into parser)
int ast_has_error(const t_ast *node);
int ast_is_valid(const t_ast *node);

// debug
const char *node_type_name(t_ast_type type);
void print_ast(const t_ast *node, int depth);

// matrix utils (to move into libft) -> THEY ARE THERE TO TEST
size_t mtx_count(void **matrix);
void mtxfree(void **mtx, void(f)(void *));
void mtxfree_n(void **mtx, size_t dim, void (*f)(void *));
void **mtxdup(void **mtx, void *(c)(void *), void(f)(void *));
void **mtxdup_n(void **mtx, size_t dim, void *(c)(void *), void(f)(void *));

// required to use libft utils for matrix
void *copy_string(void *ptr);
void print_string_matrix(char **matrix);
void free_string(void *row);

// TODO:
void ast_traverse_pre(t_ast *node, void (*visit)(t_ast *));
void ast_traverse_post(t_ast *node, void (*visit)(t_ast *));
// t_ast **ast_filter(t_ast *root, int (*predicate)(const t_ast *), size_t *count);
// t_ast **ast_leaf_nodes(t_ast *root, size_t *out_count);
// t_ast **ast_flatten_pre(t_ast *root, size_t *out_count);
// t_ast **ast_flatten_post(t_ast *root, size_t *out_count);
void ast_traverse_level(t_ast *node, void (*visit)(t_ast *));

// ast_filter
// level_trasversal
// pre/post-order trasversal
// flatten
// leaf-nodes
#endif
