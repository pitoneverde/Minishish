/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:13:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/06 17:38:20 by plichota         ###   ########.fr       */
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
	
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_TRUNC);
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
	int pipefd[2];
	char *line;
	char *delim;
	
	(void) shell;
	if (!ast || !ast->right)
		return (-1);

	delim = ast->right->value;
	
	// Crea una pipe per comunicare tra processo padre e figlio
	if (pipe(pipefd) == -1) {
		perror("pipe");
		return (-1);
	}

	// Scrive tutto l'input nella pipe
	while (1) {
		line = readline("heredoc> ");
		if (!line || strcmp(line, delim) == 0)
			break;
		write(pipefd[1], line, strlen(line));
		write(pipefd[1], "\n", 1);  // Aggiungi newline
		free(line);
	}
	free(line);
	close(pipefd[1]);  // Chiudi lato scrittura

	// Restituisce l'FD di lettura (pipefd[0]) per essere usato come stdin
	return (pipefd[0]);
}
