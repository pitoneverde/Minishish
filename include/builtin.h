/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 16:03:23 by plichota          #+#    #+#             */
/*   Updated: 2025/07/09 22:53:04 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#if !defined(BUILTIN_H)
# define BUILTIN_H

# include "ast.h"
# include "shell.h"

// echo
int		is_valid_flag_n(const char *arg);
int		execute_builtin_echo(t_ast *ast, int fd_out);

// pwd
int		execute_builtin_pwd(t_ast *ast, int fd_out);

// exit
int		execute_builtin_exit(t_ast *ast, t_sh *shell);

// cd
void	update_pwd_env(t_sh *shell, char *oldpwd);
int		execute_builtin_cd(t_ast *ast, t_sh *shell);

// env
int		execute_builtin_env(t_ast *ast, int fd_out, t_sh *shell);

// export
void	print_export_entry(char *entry, int fd_out);
void	print_export_arr(char **arr, int fd_out);
void	bubble_sort_arr(char **arr);
int		print_env_export(t_list *env, int fd_out);

void	split_env(char *str, char **key, char **val);
int		execute_builtin_export(t_ast *ast, int fd_out, t_sh *shell);

// unset
int		execute_builtin_unset(t_ast *ast, t_sh *shell);

#endif