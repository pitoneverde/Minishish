/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/06/25 17:57:47 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)	argc;
	(void)	argv;
	char	*line;
	t_sh	shell;

	shell.env = envp_to_env(envp);
	shell.last_code = 0;
	shell.is_interactive = isatty(STDIN_FILENO);
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
			break ;
		add_history(line);
		t_ast *tree = read_command_line(line);
		expand_ast(tree, &shell);
		if (tree)
			shell.last_code = executor(tree, STDIN_FILENO, &shell); // restituisce status code
		free(line);
	}
	rl_clear_history();
	free_all(&shell);
    printf("exit\n");
	return (0);
}