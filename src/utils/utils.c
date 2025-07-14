/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:22:58 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:17:09 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(t_sh *shell, char *envp[])
{
	shell->env = envp_to_env(envp);
	shell->last_code = 0;
	shell->is_interactive = isatty(STDIN_FILENO);
}

t_ast	*read_command_line(const char *line)
{
	const char	*err;
	t_list		*raw;
	t_list		*lexed;
	t_ast		*tree;

	if (!*line)
		return (NULL);
	raw = tokenize(line);
	if (!raw)
		return (NULL);
	lexed = lex(raw);
	if (!lexed)
		return (NULL);
	tree = parse(lexed);
	if (!tree)
		return (NULL);
	err = ast_get_error(tree);
	if (err)
	{
		printf("❌ Parse error: %s\n", err);
		return (NULL);
	}
	free_raw_tokens(&raw);
	free_token_list(&lexed);
	return (tree);
}

void	cleanup_and_exit(char *path, char **envp, int exit_code, char *err_msg)
{
	if (err_msg)
		perror(err_msg);
		// TO DO dprintf(STDERR_FILENO, "%s", err_msg);
	free(path);
	mtxfree_str(envp);
	exit(exit_code);
}

void	free_all(t_sh *shell)
{
	if (shell)
		free_env(shell->env);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
