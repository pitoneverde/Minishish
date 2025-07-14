/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 19:30:30 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 14:57:40 by plichota         ###   ########.fr       */
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
	int	fd;

	(void) shell;
	fd = open(ast->right->value, O_RDONLY);
	if (fd == -1)
		perror(ast->right->value);
	return (fd);
}

// ritorna fd aperto o -1 se errore
int	handle_redir_out(t_ast *ast, t_sh *shell)
{
	int	fd;

	(void) shell;
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		perror(ast->right->value);
	return (fd);
}

int	handle_append(t_ast *ast, t_sh *shell)
{
	int	fd;

	(void)shell;
	fd = open(ast->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}
