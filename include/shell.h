/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 20:03:29 by sabruma           #+#    #+#             */
/*   Updated: 2025/06/21 20:05:26 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "list.h"

typedef struct s_sh
{
	t_list	*env;		// list of t_env
	int		last_code;		// for $?
	int		is_interactive; // set if running interactively
}	t_sh;

#endif