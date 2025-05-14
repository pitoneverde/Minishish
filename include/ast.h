#ifndef AST_H
# define AST_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIR_IN,
	AST_REDIR_OUT,
	AST_APPEND,
	AST_HEREDOC,
	AST_ERROR
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type type;
	struct s_ast *left;
	struct s_ast *right;
	char *value;
	char **argv;
	// t_redir *redir;
	char *error;
}	t_ast;

t_ast *ast_new(t_ast_type type, char *value);

void ast_attach_left(t_ast *parent, t_ast *child);
void ast_attach_right(t_ast *parent, t_ast *child);
void free_ast(t_ast *tree);
void free_char_matrix(char **matrix);
// debug
const char *node_type_name(t_ast_type type);
void print_ast(const t_ast *node, int depth);

#endif
