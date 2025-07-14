/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:52:51 by plichota          #+#    #+#             */
/*   Updated: 2025/07/14 17:48:57 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_PERMISSION_DENIED 126
# define EXIT_CMD_NOT_FOUND 127

# include "shell.h"
# include "libft.h"
# include "ast.h"
# include "parser.h"
# include "expansion.h"
# include "signals.h"
# include "executor.h"
# include "builtin.h"
# include "redirections.h"

# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

// Parse line
t_ast	*read_command_line(const char *line);

// Process utils
void	init_process(t_process_data *process);
void	cleanup_and_exit(t_sh *shell, int exit_code);

// Utils
void	init_shell(t_sh *shell, char *envp[]);
void	free_all(t_sh *shell);
int		is_numeric(const char *str);

void	print_string_matrix(char **matrix);
void	*copy_string(void *str);

#endif