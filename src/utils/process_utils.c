/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 20:27:48 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:41:42 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_process(t_process_data *process)
{
	process->path = NULL;
	process->envp = NULL;
	process->fd_in = STDIN_FILENO;
	process->fd_out = STDOUT_FILENO;
	process->is_in_pipeline = 0;
	process->is_fork = 0;
}

void	cleanup_and_exit(t_sh *shell, int exit_code)
{
	t_process_data	*process;

	process = &shell->process;
	free_all(shell);
	if (exit_code == EXIT_CMD_NOT_FOUND)
		perror("Command not found");
	else if (exit_code == EXIT_PERMISSION_DENIED)
		perror("Permission denied");
	free(process->path);
	mtxfree_str(process->envp);
	close(process->fd_in);
	close(process->fd_out);
	exit(exit_code);
}
