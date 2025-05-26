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

typedef struct s_ast_filter_ctx
{
	int (*predicate)(const t_ast *);
	t_list *matches;
} t_ast_filter_ctx;

// create generic
t_ast *ast_new(t_ast_type type, char *value);

// create type command
t_ast *ast_cmd(char **argv);

// 	create 	
// 	AST_PIPE,
// 	AST_REDIR_IN,
// 	AST_REDIR_OUT,
// 	AST_APPEND,
// 	AST_HEREDOC,
t_ast *ast_binary_op(t_ast_type type, char *op, t_ast *left, t_ast *right);

t_ast *ast_error(char *msg);

// core
void ast_attach_left(t_ast *parent, t_ast *child);
void ast_attach_right(t_ast *parent, t_ast *child);
void free_ast(t_ast *tree);
void free_ast_void(void *tree);			// BAD need to create safe macros for ft_lst* where function arg
t_ast *astdup(const t_ast *node);

// utils
int ast_find(t_ast *node, const char *value);
void ast_map(t_ast *node, void (*f)(t_ast *));
void ast_replace_subtree(t_ast **target, t_ast *replace);
char *ast_to_string(const t_ast *node);

// to_string
void ast_stringify(t_ast *node);

// types of nodes
int ast_is_operator(const t_ast *node);
int ast_is_command(const t_ast *node);
int ast_is_simple_pipeline(const t_ast *node);
int ast_is_redirection_chain(const t_ast *node);
int ast_is_leaf(const t_ast *node);

// errors and validation (also to move into parser)
int ast_has_error(const t_ast *node);
int ast_is_valid(const t_ast *node);

// debug
const char *node_type_name(t_ast_type type);
void print_ast(const t_ast *node, int depth);

// required to use libft utils
t_ast **ast_lst_to_array(t_list *lst);
t_ast **ast_lst_to_array_n(t_list *lst, size_t *dim);

// traversal
void ast_traverse_pre(t_ast *node, void (*visit)(t_ast *));
void ast_traverse_pre_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data);
void ast_traverse_post(t_ast *node, void (*visit)(t_ast *));
void ast_traverse_post_ctx(t_ast *node, void (*visit)(t_ast *, void *), void *data);

// filtering
t_ast **ast_filter(t_ast *root, int (*predicate)(const t_ast *));
t_ast **ast_filter_n(t_ast *root, int (*predicate)(const t_ast *), size_t *dim);
t_ast **ast_leaf_nodes(t_ast *root);
t_ast **ast_leaf_nodes_n(t_ast *root, size_t *dim);

// flattening
t_ast **ast_flatten_pre(t_ast *root, size_t *dim);
t_ast **ast_flatten_post(t_ast *root, size_t *dim);

// TODO:
// void ast_traverse_level(t_ast *node, void (*visit)(t_ast *));
// in-order traversal (only for lib, not useful for minishish)
// level_trasversal
#endif
