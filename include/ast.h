#ifndef AST_H
# define AST_H

typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_REDIR
}	t_ast_type;

typedef struct s_ast
{
	t_ast_type type;
	struct s_ast *left;
	struct s_ast *right;
	char **argv;
	// t_redir *redir;
	char *error;
}	t_ast;

#endif
