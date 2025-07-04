/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 18:50:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/04 21:29:11 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
O_CREAT	Crea il file se non esiste
O_WRONLY	Scrittura solamente
O_TRUNC	Tronca il file se esiste (>)
O_APPEND	Aggiunge in fondo al file (>>)
O_RDONLY	Lettura solamente (<)
*/

// apre i file e imposta fd_in/fd_out (poi spawn_command e execute_command faranno il resto)
int execute_redirection_chain(t_ast *ast, t_sh *shell, int is_fork, int is_in_pipeline)
{
	char	*filename;
	int	fd_in;
	int	fd_out;
	int status;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (!ast)
		return (perror("Invalid redirection chain"), 1);

	if (ast->type == AST_REDIR_IN)
	{
		filename = ast->right->value;
		fd_in = open(filename, O_RDONLY, 0644);
		if (fd_in < 0)
		{
			perror("open");
			return (1);
		}
		if (!ast->left)
			return(perror("missing command after redirection"), 1);
		status = executor(ast->left, fd_in, fd_out, shell, is_fork, is_in_pipeline);
		close(fd_in);
		return (status);
	}
	return (1);
}