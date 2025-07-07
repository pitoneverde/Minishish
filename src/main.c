/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 17:48:28 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)	argv;
	t_sh	shell;
	t_ast	*tree;
	char	*line;
	int		status;

	init_shell(&shell, envp);
	init_signals();
	if (argc != 1)
		return (perror("Wrong number of arguments"), 0);
	while (1)
	{
		line = readline("> ");
		if (g_signal_status != 0)
		{
			shell.last_code = g_signal_status;
			g_signal_status = 0;
		}
		if (!line)
			continue ;
		if (ft_strlen(line) > 0)
			add_history(line);
		tree = read_command_line(line);
		expand_ast(tree, &shell);
		if (!tree)
		{
			perror("Generic parser error");
			continue ;
		}
		status = preprocess_redirections(tree, &shell);
		if (status == -1)
			perror("preprocessor");
		shell.last_code = executor(tree, STDIN_FILENO, STDOUT_FILENO, &shell, 0, 0); // restituisce status code
		ast_free(tree);
		free(line);
	}
	rl_clear_history();
	free_all(&shell);
	printf("exit\n");
	return (0);
}