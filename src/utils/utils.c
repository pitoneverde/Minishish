/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:22:58 by plichota          #+#    #+#             */
/*   Updated: 2025/06/21 19:02:14 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast *read_command_line(const char *line)
{
	t_list	*raw;
	t_list	*lexed;
	t_ast	*tree;

	raw = tokenize(line);
	if (!raw)
		return (NULL);
	lexed = lex(raw);
	if (!lexed)
		return(NULL);
	tree = parse(lexed);
	if (!tree)
		return (NULL);
	if (ast_has_error(tree))
		printf("❌ Parse error: %s\n", tree && tree->error ? tree->error : "unknown");
	free_raw_tokens(&raw);
	free_token_list(&lexed);
	return(tree);
}

void	free_all(t_sh *shell)
{
	if (shell)
		free_env(shell->env);
}