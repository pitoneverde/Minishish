/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:16:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_loop(t_sh *shell, t_ast *tree, char *line, int *status);

// It handles Ctrl+D with if (!line) break; 
int	main(int argc, char *argv[], char *envp[])
{
	t_sh	shell;
	t_ast	*tree;
	char	*line;
	int		status;

	status = 0;
	tree = NULL;
	line = NULL;
	(void) argv;
	init_shell(&shell, envp);
	init_signals();
	if (argc != 1)
		return (perror("Wrong number of arguments"), 0);
	main_loop(&shell, tree, line, &status);
	rl_clear_history();
	free_all(&shell);
	printf("exit\n");
	return (0);
}

// executor restituisce status code
static void	main_loop(t_sh *shell, t_ast *tree, char *line, int *status)
{
	while (1)
	{
		line = readline("> ");
		if (g_signal_status != 0)
		{
			shell->last_code = g_signal_status;
			g_signal_status = 0;
		}
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
			add_history(line);
		tree = read_command_line(line);
		expand_ast(tree, shell);
		if (!tree)
			continue ;
		*status = preprocess_redirections(tree, shell);
		if (*status == -1)
			perror("redirection error");
		shell->last_code = executor(tree,
				STDIN_FILENO, STDOUT_FILENO, shell, 0, 0);
		ast_free(tree);
		free(line);
	}
}
