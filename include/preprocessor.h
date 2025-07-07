/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plichota <plichota@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:31:24 by plichota          #+#    #+#             */
/*   Updated: 2025/07/07 18:25:36 by plichota         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

int		get_redir_fd(t_ast *redir, t_sh *shell);
int		apply_redirection(t_ast *ast, t_sh *shell);

int		preprocess_redirections(t_ast *node, t_sh *shell);
