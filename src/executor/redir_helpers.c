/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:13:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/06 22:12:01 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
O_CREAT		Crea il file se non esiste
O_WRONLY	Scrittura solamente
O_TRUNC		Tronca il file se esiste (>)
O_APPEND	Aggiunge in fondo al file (>>)
O_RDONLY	Lettura solamente (<)
*/

// ritorna fd aperto o -1 se errore
int	handle_redir_in(t_ast *ast, t_sh *shell)
{
	(void) shell;
	int fd;
	
	fd = open(ast->right->value, O_RDONLY);
	if (fd == -1)
		perror(ast->right->value); // to do
	return (fd); 
}

// ritorna fd aperto o -1 se errore
int	handle_redir_out(t_ast *ast, t_sh *shell)
{
	(void) shell;
	int fd;
	
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(ast->right->value); // to do
	return (fd); 
}

int	handle_append(t_ast *ast, t_sh *shell)
{
	int	fd;

	(void)shell;
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), -1); // to do
	return (fd);
}

int	handle_heredoc(t_ast *ast, t_sh *shell)
{
	int fd[2];
	char *line;
	char *delim;
	
	(void) shell;
	if (!ast || !ast->right)
		return (-1);
	delim = ast->right->value;
	if (pipe(fd) == -1)
		return (perror("pipe"), -1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || strcmp(line, delim) == 0)
			break;
		write(fd[1], line, strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	free(line);
	close(fd[1]);
	return (fd[0]);
}
