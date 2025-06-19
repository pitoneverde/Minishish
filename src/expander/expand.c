#include "expansion.h"

// $var -> $var value
// Core expansion entry point
void	expand_ast(t_ast *root, t_sh *shell)
{
	ast_traverse_post_ctx(root, should_expand_token, shell);
}

void	should_expand_token(t_ast *node, void *ctx)
{
	t_sh	*shell;

	shell = (t_sh *)ctx;
	if (!node)
		return ;
	if (node->type == AST_COMMAND)
		expand_command_args(node, shell);
	else if (node->value && node->quote != S_QUOTE)
		expand_token_value(node, shell);
}

// Expands any other token->value field (except commands)
void expand_token_value(t_ast *node, t_sh *shell)
{
	char *exp;

	exp = expand_token(node->value, node->quote, shell);
	free(node->value);
	node->value = exp;
}

// Expands a command node's arguments and fills argv/argc
void	expand_command_args(t_ast *cmd, t_sh *shell)
{
	char	*exp_str;
	t_ast	*arg;
	t_list	*exp;
	t_list	*curr;

	exp = NULL;
	curr = cmd->args;
	while (curr)
	{
		arg = (t_ast *)curr->content;
		exp_str = expand_token(arg->value, arg->quote, shell);
		if (arg->quote == N_QUOTE)
			split_command_args(&exp, exp_str);
		else
			ft_lstadd_back(&exp, ft_lstnew(ft_strdup(exp_str)));
		free(exp_str);
	}
	cmd->argc = ft_lstsize(exp);
	cmd->argv = (char **)lst_to_array(exp);
	ft_lstclear(&exp, free);
}

void	split_command_args(t_list **exp, char *exp_str)
{
	int		i;
	char	**words;

	words = ft_split(exp_str, ' ');
	i = 0;
	while (words && words[i])
	{
		ft_lstadd_back(exp, ft_lstnew(ft_strdup(words[i])));
		i++;
	}
	mtxfree_str(words);
}

// Expands a single token string (e.g., "hello$USER") according to quote type
char	*expand_token(const char *str, t_quote_type quote, t_sh *shell)
{
	
}

// Handles heredoc input, expands lines only if delimiter is unquoted
char	*read_heredoc(const char *delimiter, t_quote_type quote, t_sh *shell)
{
	(void)delimiter;
	(void)quote;
	(void)shell;
	return (NULL);
}
