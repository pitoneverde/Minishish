#if !defined(EXPANSION_H)
# define EXPANSION_H

# include "minishell.h"

// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell);

// operation for each node
void	should_expand_token(t_ast *node, void *ctx);

// Expands a command node's arguments and fills argv/argc
void	expand_command_args(t_ast *cmd, t_sh *shell);
void	split_command_args(t_list **exp, char *exp_str);

// Expands any other token->value field (except commands)
void	expand_token_value(t_ast *token, t_sh *shell);

// Expands a single token string (e.g., "hello$USER") according to quote type
char	*expand_token(const char *str, t_quote_type quote, t_sh *shell);

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell);

// // Utility: convert a list of strings into a null-terminated char** array
// char	**lst_to_str_array(t_list *lst);

// // Optional: exit status used by $?
// extern int g_exit_code;

#endif // EXPANSION_H
