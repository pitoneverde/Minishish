/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:30:30 by plichota          #+#    #+#             */
/*   Updated: 2025/07/11 00:03:38 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_loop(char *delim, int fd_out)
{
	char *line;

	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delim) == 0)
			break;
		// to do controllare espansione variabili
		// char *expanded = expand_variables(line, shell);
		// ft_putendl_fd(expanded, fd_out);
		// free(expanded);
		write(fd_out, line, ft_strlen(line));
		write(fd_out, "\n", 1);
		free(line);
	}
	free(line);
	return (0);
}

// handles heredoc with the buffer of the pipe instead of a temp file
// uses close(STDIN_FILENO) for exiting the loop with Ctrl-C
// and then resets it
int	handle_heredoc(t_ast *ast, t_sh *shell)
{
	int fd[2];
	int saved_stdin;
	struct sigaction	old_sa;
	struct sigaction	new_sa;
	
	(void) shell;
	if (!ast || !ast->right)
		return (-1);
	// save old struct
	if (sigaction(SIGINT, NULL, &old_sa) == -1)
		return (perror("sigaction get"), -1);
	// dup stdin
	saved_stdin = dup(STDIN_FILENO); // --------------------- close saved_stdin
	if (saved_stdin == -1)
		return (perror("dup stdin"), -1);
	// init new struct
	sigemptyset(&new_sa.sa_mask);
	new_sa.sa_handler = handler_sigint_heredoc;
	new_sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &new_sa, NULL) == -1) // ---------- revert struct
		return (perror("sigaction set"), close(saved_stdin), -1);
	// create pipe ------------------------------------------ close fds
	if (pipe(fd) == -1)
	{
		sigaction(SIGINT, &old_sa, NULL);
		close(saved_stdin);
		return (perror("pipe"), -1);
	}
	g_signal_status = 0; // to do serve davvero?
	// loop
	heredoc_loop(ast->right->value, fd[1]);
	// Restore
	perror("restore old\n");
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
	close(fd[1]);
	sigaction(SIGINT, &old_sa, NULL);
	// (if ctrl-c) update status and close the entire pipe
	if (g_signal_status == EXIT_SIGINT)
	{
		perror("ctrl + c detected");
		shell->last_code = EXIT_SIGINT;
		g_signal_status = 0;
		return (close(fd[0]), -1);
	}
	// otherwise the read enpoint remains open
	return (fd[0]);
}
