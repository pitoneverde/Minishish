/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 04:39:29 by sabruma           #+#    #+#             */
/*   Updated: 2025/07/09 19:13:07 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"

// Expands any other token->value field (except commands)
void	expand_token_value(t_ast *node, t_sh *shell)
{
	char	*exp;

	exp = expand_token(node->value, node->quote, shell);
	if (!exp)
	{
		node->error = ft_strdup("expansion error");
		return ;
	}
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
		if (!exp_str)
		{
			cmd->error = ft_strdup("expansion error");
			return (ft_lstclear(&exp, NULL));
		}
		if (arg->quote == N_QUOTE)
			split_command_args(&exp, exp_str);
		else
			ft_lstadd_back(&exp, ft_lstnew(ft_strdup(exp_str)));
		free(exp_str);
		curr = curr->next;
	}
	cmd->argc = ft_lstsize(exp);
	cmd->argv = (char **)lst_to_array(exp);
	ft_lstclear(&exp, NULL);
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

// creates a bunch of lines terminated with \n\0 from a t_list of char*
char	*lst_join(t_list *lst)
{
	t_sb	*sb;
	t_list	*node;

	if (!lst)
		return (ft_strdup(""));
	node = lst;
	sb = sb_create(64);
	if (!sb)
		return (NULL);
	while (node)
	{
		sb_append_str(sb, (char *)node->content);
		sb_append_char(sb, '\n');
		node = node->next;
	}
	return (sb_build(sb));
}
