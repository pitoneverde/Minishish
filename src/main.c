/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:51:36 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:59:00 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exit_heredoc_sigint into last status?
void	main_loop(t_sh *shell)
{
	int		status;

	while (1)
	{
		init_process(&shell->process);
		shell->line = readline("> ");
		update_signal_status(shell);
		if (!shell->line)
			break ;
		shell->tree = read_command_line(shell->line);
		expand_ast(shell->tree, shell);
		shell->last_code = 0;
		if (!shell->tree)
			continue ;
		if (ft_strlen(shell->line) > 0)
			add_history(shell->line);
		status = process_ast_redirections(shell->tree, shell);
		if (status >= 0)
			shell->last_code = executor(shell->tree, shell);
		ast_free(shell->tree);
		free(shell->line);
		shell->line = NULL;
		shell->tree = NULL;
	}
}

// It handles Ctrl+D with if (!line) break;
int	main(int argc, char *argv[], char *envp[])
{
	t_sh	shell;

	(void) argv;
	shell = (t_sh){0};
	init_shell(&shell, envp);
	init_signals();
	if (argc != 1)
		return (perror("Wrong number of arguments"), 0);
	main_loop(&shell);
	rl_clear_history();
	free_all(&shell);
	printf("exit\n");
	return (0);
}
