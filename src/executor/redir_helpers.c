/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 23:13:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/05 23:39:21 by plichota         ###   ########.fr       */
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
int	handle_redir_in(t_ast *node, t_sh *shell)
{
	(void) shell;
	int fd;
	
	fd = open(node->right->value, O_RDONLY);
	if (fd == -1)
		perror(node->right->value); // to do
	return (fd); 
}

// ritorna fd aperto o -1 se errore
int	handle_redir_out(t_ast *node, t_sh *shell)
{
	(void) shell;
	int fd;
	
	fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		perror(node->right->value); // to do
	return (fd); 
}

int	handle_append(t_ast *node, t_sh *shell)
{
	int	fd;

	(void)shell;
	fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), -1); // to do
	return (fd);
}

int	handle_heredoc(t_ast *node, t_sh *shell)
{
	return (0); // to do
}
